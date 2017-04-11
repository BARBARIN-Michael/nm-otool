/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 17:18:08 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/10 18:39:46 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include "otool.h"

struct mach_header		get_header(const void *mem)
{
	static struct mach_header header;

	if (mem != (void *)0)
		header = *(struct mach_header*)mem;
	return (header);
}
