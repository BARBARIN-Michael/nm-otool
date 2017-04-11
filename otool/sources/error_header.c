/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 14:48:08 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/10 18:39:45 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include "libft.h"
#include <stdlib.h>

void		error_header(const char *error)
{
	ft_putendl_fd(error, STDERR_FILENO);
}
