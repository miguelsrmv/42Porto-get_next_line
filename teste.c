/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:43:36 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/05/07 16:08:44 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>

int	main(void)
{
	int		fd;
	char	*filename;
	int		i;

	filename = "testfiles/mytest";
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	i = 0;
	while (i < 9)
	{
		printf("\nString %i: %s", i + 1, (get_next_line(fd)));
		i++;
	}
	close(fd);
}
