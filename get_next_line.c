/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:31:09 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/05/10 16:41:24 by mde-sa--         ###   ########.fr       */
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
	char			*buffer;
	static char		*oldbuffer;

	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!fd)
		return (NULL);
	if (oldbuffer && ft_strchr(oldbuffer, '\n'))
		return (handle_newline(buffer, &oldbuffer, 1));
	read(fd, buffer, BUFFER_SIZE);
	if (buffer[0] == '\0')
	{
		if (oldbuffer)
			return (oldbuffer);
		return ("");
	}
	if (oldbuffer)
	{
		buffer = ft_strjoin(oldbuffer, buffer);
		oldbuffer = "";
	}
	if (ft_strchr(buffer, '\n'))
		return (handle_newline(buffer, &oldbuffer, 2));
	return (ft_strjoin(buffer, get_next_line(fd)));
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