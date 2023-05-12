/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:09:07 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/05/12 21:10:30 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

char	*line_from_old_buffer(char **oldbuffer)
{
	char	*left_buffer;
	char	*right_buffer;
	int		size;

	size = ft_strchr(*oldbuffer, '\n') - *oldbuffer;
	left_buffer = ft_substr(*oldbuffer, 0, size);
	right_buffer = ft_strdup(ft_strchr(*oldbuffer, '\n') + 1);
	free(*oldbuffer);
	*oldbuffer = right_buffer;
	return (left_buffer);
}

char	*handle_readlen(char *buffer, char *oldbuffer, ssize_t read_len)
{
	char	*temp;

	free(buffer);
	if (read_len == 0)
	{
		temp = ft_strdup(oldbuffer);
		free(oldbuffer);
		return (temp);
	}
	free(oldbuffer);
	return (NULL);
}

char	*join_buffers(char *oldbuffer, char *buffer)
{
	char	*newstr;

	newstr = ft_strjoin(oldbuffer, buffer);
	free(oldbuffer);
	free(buffer);
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	*oldbuffer;
	char		*buffer;
	ssize_t		read_len;

	if (fd < 0 || !fd || BUFFER_SIZE <= 0)
		return (NULL);
	if (oldbuffer && ft_strchr(oldbuffer, '\n'))
		return (line_from_old_buffer(&oldbuffer));
	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	read_len = read(fd, buffer, BUFFER_SIZE);
	if (read_len)
		buffer[read_len] = '\0';
	if (read_len <= 0)
		return (handle_readlen(buffer, oldbuffer, read_len));
	if (oldbuffer)
		oldbuffer = join_buffers(oldbuffer, buffer);
	else
		oldbuffer = buffer;
	if (ft_strchr(oldbuffer, '\n'))
		return (line_from_old_buffer(&oldbuffer));
	return (get_next_line(fd));
}
/*
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int	main(void)
{
	int		fd;
	char	*filename;
	int		i;

	filename = "testfiles/mix1";
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	i = 0;
	while (i < 3)
	{
		printf("String %i: %s**\n", i + 1, (get_next_line(fd)));
		i++;
	}
	close(fd);
}
*/