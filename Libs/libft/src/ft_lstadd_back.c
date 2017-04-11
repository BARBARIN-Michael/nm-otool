/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/22 23:10:34 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/05 14:44:00 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *temp;

	if (new)
	{
		if (!(*alst))
		{
			*alst = new;
			return ;
		}
		temp = *alst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_lstadd_before(t_list **alst, t_list *ec, t_list *ne)
{
	t_list	*tmp;
	t_list	*before;

	tmp = *alst;
	before = tmp;
	while (tmp != NULL)
	{
		if (tmp == ec)
		{
			if (before != tmp)
				before->next = ne;
			ne->next = tmp;
			break ;
		}
		tmp = tmp->next;
	}
}
