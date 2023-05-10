/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:31:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/05/10 18:18:41 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*oldbuffer;
	char		*buffer;
	char		*temp;
	ssize_t		read_len;

	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer)
		return (NULL);
	if (oldbuffer && ft_strchr(oldbuffer, '\n'))
	{
		temp = handle_newline(buffer, &oldbuffer, 1);
		free(buffer);
		return (temp);
	}
	read_len = read(fd, buffer, BUFFER_SIZE);
	buffer[read_len] = '\0';
	if (read_len <= 0)
	{
		free(buffer);
		if (read_len == 0)
			temp = oldbuffer;
		else
			temp = NULL;
		oldbuffer = NULL;
		return (temp);
	}
	if (oldbuffer)
	{
		temp = ft_strjoin(oldbuffer, buffer);
		free(buffer);
		buffer = temp;
		oldbuffer = NULL;
	}
	if (ft_strchr(buffer, '\n'))
		return (handle_newline(buffer, &oldbuffer, 2));
	oldbuffer = buffer;
	return (get_next_line(fd));
}

/*
int	main(void)
{
	int		fd;
	char	*filename;
	int		i;

	filename = "testfiles/zero_byte";
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	i = 0;
	while (i < 1001)
	{
		printf("String %i: %s**\n", i + 1, (get_next_line(fd)));
		fflush(stdout);
		i++;
	}
	close(fd);
}
*/