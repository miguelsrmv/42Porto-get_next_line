/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:09:07 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/05/20 10:59:14 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>

char	*ft_get_text(int fd, char *buffer)
{
	char		*temp_buffer;
	ssize_t		read_len;

	temp_buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!temp_buffer)
		return (NULL);
	read_len = 1;
	while (!ft_strchr(buffer, '\n') && read_len > 0)
	{
		read_len = read(fd, temp_buffer, BUFFER_SIZE);
		if (read_len == -1)
		{
			free(temp_buffer);
			free(buffer);
			return (NULL);
		}
		temp_buffer[read_len] = '\0';
		buffer = ft_strjoin(buffer, temp_buffer);
	}
	free(temp_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_get_text(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_strtrim_l(buffer, '\n');
	buffer = ft_strtrim_r(buffer, '\n');
	return (line);
}
