/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 11:51:41 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/10 18:39:45 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include "libft.h"
#include <stdlib.h>

void		error_file(const char *exe, const char *file, const char *error)
{
	ft_putstr_fd(exe, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
