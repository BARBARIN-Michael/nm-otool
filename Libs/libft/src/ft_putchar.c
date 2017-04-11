/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 17:07:22 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/07 18:36:22 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putwchar(wchar_t c)
{
	write(1, &c, 1);
}

void	ft_putnchar(char c, int i)
{
	char		str[255];
	int			a;

	a = 0;
	if (i > 254 || i <= 0)
		return ;
	while (a < i)
	{
		str[a] = c;
		++a;
	}
	str[a] = '\0';
	ft_putstr(str);
}
