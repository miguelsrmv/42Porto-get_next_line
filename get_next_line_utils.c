/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:09:00 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/05/20 10:59:25 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

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
	char	*substring;
	int		i;

	if (!buffer)
		return (NULL);
	substring = malloc((ft_strchr(buffer, '\n') - buffer) * sizeof(char) + 1);
	if (!substring)
		return (NULL);
	while (buffer[i] != c)
		substring[i] = buffer[i];
	substring[i] = '\0';
	return (substring);
}

char	*ft_strtrim_r(char *buffer, char c)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != c)
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	next_line = malloc(sizeof(char) * (ft_strlen(buffer) - i));
	if (!buffer)
		return (NULL);
	j = -1;
	while (++i < ft_strlen(buffer))
		next_line[++j] = buffer[i];
	next_line[++j] = '\0';
	free(buffer);
	return (next_line);
}
