/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:41:34 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/11 11:13:33 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		print_hex(uint64_t ptr)
{
	char		*str;

	if (!(str = ft_ntoa(ptr, BASE16)))
		return ;
	if (get_header(NULL).magic == MH_MAGIC
			|| get_header(NULL).magic == MH_CIGAM)
		ft_putnchar('0', 8 - ft_strlen(str));
	else
		ft_putnchar('0', 16 - ft_strlen(str));
	ft_putstr(str);
	free(str);
}

void		print_null(void)
{
	if (get_header(NULL).magic == MH_MAGIC)
		ft_putnchar(' ', 8);
	else
		ft_putnchar(' ', 16);
}

int			print_type(t_item_sym *sym, int *seg)
{
	int			type;

	type = -1;
	if ((sym->n_type & N_STAB))
		return (type);
	else if ((sym->n_type & N_TYPE) == N_ABS)
		type = 'A';
	else if ((sym->n_type & N_TYPE) == N_UNDF)
		type = 'U';
	else if ((sym->n_type & N_TYPE) == N_INDR)
		type = 'I';
	else if ((sym->n_type & N_TYPE) == N_SECT)
		type = seg[sym->n_sect - 1];
	if (!(sym->n_type & N_EXT))
		type = ft_tolower(type);
	return (type);
}

void		print_content(t_list *elem, int *seg)
{
	char		*str;
	uint64_t	ptr;
	int			type;

	while (elem != NULL)
	{
		str = ((t_item_sym *)elem->content)->str;
		ptr = ((t_item_sym *)elem->content)->ptr;
		type = print_type((t_item_sym *)elem->content, seg);
		if (type != -1)
		{
			if (type == 'U' || type == 'u')
				print_null();
			else
				print_hex(ptr);
			ft_putstr(" ");
			ft_putchar(type);
			ft_putstr(" ");
			ft_putendl(str);
		}
		elem = elem->next;
	}
}
