/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 11:02:33 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/10 18:39:45 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <sys/stat.h>
#include "libft.h"
#include "otool.h"

int		main(int ac, char **av)
{
	void			*data;
	struct stat		buf;

	if (ac < 2)
		error_usage(av[0]);
	data = handle_open(av[0], av[ft_array_count((void **)av) - 1], &buf);
	handle_parse(data);
	handle_close(data, &buf);
	return (0);
}
