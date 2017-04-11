/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 11:27:06 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/10 18:39:45 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "otool.h"

void		*handle_open(const char *exe, const char *file, struct stat *buf)
{
	int				fd;

	if ((fd = open(file, O_RDONLY)) <= 0)
		error_file(exe, file, "No such file or permission denied.");
	if (fstat(fd, buf) != 0)
		error_file(exe, file, "No such file or directory.");
	else if (!(buf->st_mode & S_IREAD))
		error_file(exe, file, "Permission denied.");
	else if (!S_ISDIR(buf->st_mode))
		return (mmap(0, buf->st_size, PROT_READ, MAP_PRIVATE, fd, 0));
	error_file(exe, file, "The file was not recognized as a valid object file");
	return (NULL);
}

void		handle_close(void *data, struct stat *buf)
{
	munmap(data, buf->st_size);
}
