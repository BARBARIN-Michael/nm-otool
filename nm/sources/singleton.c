/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 17:18:08 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/07 20:05:51 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include "nm.h"

struct mach_header		get_header(const void *mem)
{
	static struct mach_header header;

	if (mem != (void *)0)
		header = *(struct mach_header*)mem;
	return (header);
}
