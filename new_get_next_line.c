/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:09:07 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/05/20 10:24:50 by mde-sa--         ###   ########.fr       */
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

char	*ft_strtrim_l(char *buffer, char c)
{
	
}

char	*ft_strtrim_r(char *buffer, char c)
{
	
}


char	*ft_get_text(int fd, char *buffer)
{
	char		*temp_buffer;
	ssize_t		read_len;

	temp_buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!temp_buffer)
		return(NULL);
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
	buffer= ft_strtrim_r(buffer, '\n');
	return (line);
}
