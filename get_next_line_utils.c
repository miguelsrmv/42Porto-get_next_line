/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:31:22 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/05/10 18:26:08 by mde-sa--         ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char *s2)
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
	free(s1);
	return (newstr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substring = malloc(len + 1);
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

char	*handle_newline(char *buffer, char **oldbuffer, int n)
{
	int		buf_len;
	int		oldbuf_len;
	int		buf_nl;
	int		old_nl;
	char	*temp;

	buf_len = ft_strlen(buffer);
	if (n == 1)
	{
		oldbuf_len = ft_strlen(*oldbuffer);
		old_nl = ft_strchr(*oldbuffer, '\n') - *oldbuffer + 1;
		buffer = ft_substr(*oldbuffer, 0, old_nl);
		temp = ft_substr(*oldbuffer, old_nl, oldbuf_len - buf_len + 1);
		free(*oldbuffer);
		*oldbuffer = temp;
		return (buffer);
	}
	buf_nl = ft_strchr(buffer, '\n') - buffer + 1;
	if (ft_strlen(buffer) == 1)
		return ("\n");
	temp = ft_substr(buffer, 0, buf_nl);
	*oldbuffer = ft_substr(buffer, buf_nl, buf_len - buf_nl);
	return (temp);
}
