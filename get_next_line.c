/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:31:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/05/07 16:08:23 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include "get_next_line.h"

/*
ssize_t read(int fd, void *buf, size_t nbyte);
*/

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*oldbuffer;

	if (!fd)
		return(NULL);
	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (buffer == NULL)
		return (NULL);
	read(fd, buffer, BUFFER_SIZE);
	if (buffer[BUFFER_SIZE - 1] != '\n')
	{
		if (ft_strchr(buffer, '\n'))
		{
			oldbuffer = ft_strjoin(oldbuffer, buffer);
			free(buffer);
			return (oldbuffer);
		}
		else
			buffer = ft_strjoin(buffer, get_next_line(fd));
	}
	if (oldbuffer)
	{
		buffer = ft_strjoin(oldbuffer, buffer);
		free(oldbuffer);
	}
	return (buffer);
}
