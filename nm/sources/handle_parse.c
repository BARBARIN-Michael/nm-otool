/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 13:37:54 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/10 18:00:21 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "nm.h"

void			free_sym(t_list *sym)
{
	t_list	*tmp;

	while (sym)
	{
		tmp = sym->next;
		free(sym->content);
		free(sym);
		sym = tmp;
	}
}

void			handle_seg(struct section *sc, size_t len, size_t n, int *arr)
{
	int		i;

	i = -1;
	while (arr[++i] != -1)
		;
	while (n-- > 0)
	{
		if (!ft_strcmp(sc->sectname, SECT_TEXT))
			arr[i] = 'T';
		else if (!ft_strcmp(sc->sectname, SECT_DATA))
			arr[i] = 'D';
		else if (!ft_strcmp(sc->sectname, SECT_BSS))
			arr[i] = 'B';
		else
			arr[i] = 'S';
		arr[++i] = -1;
		sc = (void *)sc + len;
	}
}

void			handle_match(const void *mem, uint32_t size, uint32_t ncmds)
{
	struct load_command		*lc;
	t_list					*sym;
	static int				seg[MAX_SECT] = { -1 };
	uint32_t				i;

	if (ncmds <= 0)
		return ;
	lc = (void *)mem + size;
	i = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			sym = handle_sym((void *)mem, (struct symtab_command *)lc);
		else if (lc->cmd == LC_SEGMENT)
			handle_seg((void *)lc + sizeof(struct segment_command),
					sizeof(struct section),
					((struct segment_command *)lc)->nsects, seg);
		else if (lc->cmd == LC_SEGMENT_64)
			handle_seg((void *)lc + sizeof(struct segment_command_64),
					sizeof(struct section_64),
					((struct segment_command_64 *)lc)->nsects, seg);
		lc = (void *)lc + lc->cmdsize;
	}
	print_content(sym, seg);
	free_sym(sym);
}

void			handle_fat(void *ptr)
{
	struct fat_header	*head;
	struct fat_arch		*arch;
	uint32_t			narch;
	cpu_type_t			cputype;

	head = (struct fat_header *)ptr;
	arch = (struct fat_arch *)(ptr + sizeof(struct fat_header));
	narch = head->magic == FAT_CIGAM ? __builtin_bswap32(head->nfat_arch)
										: head->nfat_arch;
	while (narch-- > 0)
	{
		cputype = head->magic == FAT_CIGAM ? __builtin_bswap32(arch->cputype)
										: arch->cputype;
		if (cputype == CPU_TYPE_X86_64)
		{
			if (head->magic == FAT_CIGAM)
				handle_parse(ptr + __builtin_bswap32(arch->offset));
			else
				handle_parse(ptr + arch->offset);
		}
		arch = (void *)arch + sizeof(struct fat_arch);
	}
}

void			handle_parse(const void *mem)
{
	struct mach_header	header;
	uint32_t			ncmds;
	size_t				size;

	size = 0;
	header = get_header(mem);
	if (header.magic == FAT_MAGIC || header.magic == FAT_CIGAM)
	{
		handle_fat((void *)mem);
		return ;
	}
	ncmds = (header.magic == MH_MAGIC || header.magic == MH_MAGIC_64)
		? header.ncmds : __builtin_bswap32(header.ncmds);
	if (header.magic == MH_MAGIC || header.magic == MH_CIGAM)
		handle_match(mem, sizeof(struct mach_header), ncmds);
	else if (header.magic == MH_MAGIC_64 || header.magic == MH_CIGAM_64)
		handle_match(mem, sizeof(struct mach_header_64), ncmds);
	else
		error_header("The file was not recognized as a valid object file.");
}
