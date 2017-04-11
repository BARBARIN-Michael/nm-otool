/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:41:34 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/11 11:13:08 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include <stdint.h>

static void		print_2hex(uintmax_t hex, char *base)
{
	int		cmp;
	char	str[3];
	int		len;

	cmp = 0;
	len = ft_strlen(base);
	cmp = 2;
	str[cmp--] = '\0';
	while (cmp >= 0)
	{
		str[cmp--] = base[(hex % len)];
		hex /= len;
	}
	write(1, str, 2);
}

static void		print_ptr(size_t ptr)
{
	char		*str;

	if (!(str = ft_ntoa((size_t)ptr, BASE16)))
		return ;
	if (get_header(NULL).magic == MH_MAGIC
			|| get_header(NULL).magic == MH_CIGAM)
		ft_putnchar('0', 8 - ft_strlen(str));
	else
		ft_putnchar('0', 16 - ft_strlen(str));
	ft_putstr(str);
	free(str);
}

void		print_memory(char *memory, size_t size, size_t addr)
{
	size_t		i;
	int32_t		a;

	i = 0;
	print_ptr((size_t)addr);
	ft_putstr("\t");
	while (i < size)
	{
		a = 0;
		if (i > 0 && (i % 16) == 0)
		{
			write(1, "\n", 1);
			print_ptr((size_t)addr + i);
			ft_putstr("\t");
		}
		print_2hex(memory[i] & 0xFF, BASE16);
		++i;
		write(1, " ", 1);
	}
	ft_putendl("\n");
}

