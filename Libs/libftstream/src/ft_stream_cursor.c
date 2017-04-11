/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stream_cursor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbare <barbare@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 11:29:54 by barbare           #+#    #+#             */
/*   Updated: 2017/01/25 12:15:00 by barbare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_stream.h>
#include <stdio.h>
#include <libft.h>

/*
** ****************************************************************************
** ft_stream_fill
** INPUT:	Struct stream
** OUTPUT:	Nothing
** Describe: Read again after stream's create for complete element
** ****************************************************************************
*/

t_stream		ft_stream_fill(t_stream stream)
{
	char	buf[BUFFSTREAM];
	int		ret;

	buf[0] = '\0';
	if (stream.cursor > 0)
		stream = ft_stream_cr(stream);
	ret = read(stream.fdin, buf, BUFFSTREAM - stream.size);
	buf[ret] = '\0';
	ft_strcat(stream.buf, buf);
	stream.size = ft_strlen(stream.buf);
	return (stream);
}

/*
** ****************************************************************************
** ft_stream_cr
** INPUT:	Struct stream
** OUTPUT:	Nothing
** Describe: Carriage return old string to start
** ****************************************************************************
*/

t_stream		ft_stream_cr(t_stream stream)
{
	ft_strcpy(stream.buf, &stream.buf[stream.cursor]);
	stream.size = ft_strlen(stream.buf);
	stream.cursor = 0;
	return (stream);
}
