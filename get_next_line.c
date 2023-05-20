/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:09:07 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/05/17 21:06:29 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && (unsigned char)c != *s)
		s++;
	if ((unsigned char)c == *s)
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	newstr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
			newstr[i] = s1[i];
			i++;
	}
	j = 0;
	while (s2[j])
	{
			newstr[i + j] = s2[j];
			j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

char	*ft_strdup(const char *src)
{
	char	*cpy;
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	cpy = (char *)malloc(sizeof(char) * i + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (*src)
			cpy[i++] = *src++;
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	substring = malloc(len * sizeof(char) + 1);
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

char	*join_buffers(char *oldbuffer, char *buffer)
{
	char	*newstr;

	newstr = ft_strjoin(oldbuffer, buffer);
	free(oldbuffer);
	/*free(buffer);*/
	return (newstr);
}

char	*read_from_file(int fd, char *buffer, int buffer_size, ssize_t *read_len)
{
	*read_len = read(fd, buffer, buffer_size);
	if (*read_len > 0)
		buffer[*read_len] = '\0';
	else if (*read_len <= 0)
	{
	/*	free(buffer);*/
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd, int buffer_size)
{
	char		*buffer;
	static char	*old_buffer;
	ssize_t		read_len;

	if (fd < 0 || buffer_size <= 0)
		return (NULL);
	buffer = malloc(buffer_size * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	buffer = read_from_file(fd, buffer, buffer_size, &read_len);
	if (old_buffer)
		buffer = join_buffers(old_buffer, buffer);
	while (!ft_strchr(buffer, '\n') && read_len > 0)
		buffer = join_buffers(buffer, read_from_file(fd, buffer, buffer_size, &read_len));
	if (ft_strchr(buffer, '\n'))
	{
		old_buffer = ft_strdup(ft_strchr(buffer, '\n') + 1);
		buffer = ft_substr(buffer, 0, ft_strlen(buffer) - ft_strlen(old_buffer));
	}
	return (buffer);
}

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*filename;
	int		i;
	int		buffer_size;

	buffer_size = 10;
	filename = "testfiles/mytest";
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	i = 0;
	while (i < 3)
	{
		printf("String %i: %s**\n\n\n", i + 1, (get_next_line(fd, buffer_size)));
		i++;
	}
	close(fd);
}
