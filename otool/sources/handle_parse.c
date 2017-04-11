/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 13:37:54 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/11 11:12:09 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"
#include "otool.h"

static void		print_section(size_t size, char *offset, size_t addr)
{
	print_memory(offset, size, addr);
}

void			handle_seg(const void *ptr, struct section *sc, size_t len, size_t n)
{
	struct section_64	*sc64;

	if (ft_strcmp(sc->segname, SEG_TEXT))
		return ;
	while (n-- > 0)
	{
		if (!ft_strcmp(sc->sectname, SECT_TEXT))
		{
			ft_putstr("Contents of (");
			ft_putstr(sc->segname);
			ft_putstr(",");
			ft_putstr(sc->sectname);
			ft_putendl(") section");
			if (get_header(NULL).magic == MH_CIGAM || get_header(NULL).magic == MH_MAGIC)
				print_section(sc->size, (void *)ptr + sc->offset, sc->addr);
			else
			{
				sc64 = (struct section_64*)sc;
				print_section(sc64->size, (void *)ptr + sc64->offset, sc64->addr);
			}
		}
		sc = (void *)sc + len;
	}
}

void			handle_match(const void *mem, uint32_t size, uint32_t ncmds)
{
	struct load_command		*lc;
	uint32_t				i;

	if (ncmds <= 0)
		return ;
	lc = (void *)mem + size;
	i = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			handle_seg(mem, (void *)lc + sizeof(struct segment_command),
					sizeof(struct section),
					((struct segment_command *)lc)->nsects);
		else if (lc->cmd == LC_SEGMENT_64)
			handle_seg(mem, (void *)lc + sizeof(struct segment_command_64),
					sizeof(struct section_64),
					((struct segment_command_64 *)lc)->nsects);
		lc = (void *)lc + lc->cmdsize;
	}
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
