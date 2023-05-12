/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:09:00 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/05/12 19:36:26 by mde-sa--         ###   ########.fr       */
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
