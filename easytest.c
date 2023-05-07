#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>


ssize_t	ft_strlen(const char *str)
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

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*oldbuffer;
	int				BUFFER_SIZE = 3;

	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (buffer == NULL || !fd)
		return (NULL);
	read(fd, buffer, BUFFER_SIZE);
	if (oldbuffer)
	{
		buffer = ft_strjoin(oldbuffer, buffer);
		oldbuffer = "";
	}
	if (buffer[BUFFER_SIZE - 1] != '\n')  // Não funciona porque pode haver um \n antes do fim e convém dar a string logo aí
	{
		if (ft_strchr(buffer, '\n'))
		{
			oldbuffer = ft_substr(buffer, ft_strchr(buffer, '\n') - buffer + 1, ft_strlen(buffer));  //Editar isto em caos de várias \n seguidas. Não usar ft_susbtr??
			if (oldbuffer[1] == '\n')
			{
				(oldbuffer)++;
				return("\n");
			}
			return (ft_substr(buffer, 0, ft_strchr(buffer, '\n') - buffer + 1));
		}
		else
			return (ft_strjoin(buffer, get_next_line(fd)));
	}
	return (buffer);
}

int	main(void)
{
	int		fd;
	char	*filename;
	int		i;

	filename = "testfiles/1000_nl";
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	i = 0;
	while (i < 8)
	{
		printf("String %i: %s**\n", i + 1, (get_next_line(fd)));
		i++;
	}
	close(fd);
}
