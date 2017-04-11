/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sym.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:34:22 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/10 15:47:49 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

void			add_list_sym(t_list **lst, t_item_sym *item)
{
	t_list		*tmp;
	t_list		*before;

	tmp = *lst;
	before = NULL;
	while (tmp)
	{
		if (ft_strcmp(item->str, ((t_item_sym *)tmp->content)->str) < 0)
		{
			if (before == NULL)
			{
				*lst = ft_lstnew(item, sizeof(t_item_sym));
				(*lst)->next = tmp;
			}
			else
			{
				before->next = ft_lstnew(item, sizeof(t_item_sym));
				before->next->next = tmp;
			}
			return ;
		}
		before = tmp;
		tmp = tmp->next;
	}
	before->next = ft_lstnew(item, sizeof(t_item_sym));
}

t_item_sym		insert_item(void *symlst, char *str, size_t i)
{
	t_item_sym		sym;

	if (get_header(NULL).magic == MH_MAGIC)
	{
		sym.ptr = ((struct nlist *)symlst)[i].n_value;
		sym.n_type = ((struct nlist *)symlst)[i].n_type;
		sym.str = str + ((struct nlist *)symlst)[i].n_un.n_strx;
		sym.n_sect = ((struct nlist *)symlst)[i].n_sect;
		return (sym);
	}
	sym.ptr = ((struct nlist_64 *)symlst)[i].n_value;
	sym.n_type = ((struct nlist_64 *)symlst)[i].n_type;
	sym.str = str + ((struct nlist_64 *)symlst)[i].n_un.n_strx;
	sym.n_sect = ((struct nlist_64 *)symlst)[i].n_sect;
	return (sym);
}

t_list			*handle_sym(void *mem, struct symtab_command *sym)
{
	t_list		*lst;
	t_item_sym	item_sym;
	uint32_t	i;

	lst = NULL;
	i = 0;
	while (i < sym->nsyms)
	{
		item_sym = insert_item(mem + sym->symoff, mem + sym->stroff, i++);
		if (lst == NULL)
			ft_lstadd(&lst, ft_lstnew(&item_sym, sizeof(t_item_sym)));
		else
			add_list_sym(&lst, &item_sym);
	}
	return (lst);
}
