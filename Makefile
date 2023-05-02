# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 16:13:23 by mde-sa--          #+#    #+#              #
#    Updated: 2023/05/02 19:36:05 by mde-sa--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

FLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=32

all: 
	${CC} ${FLAGS} get_next_line.c get_next_line_utils.c teste.c
	./a.out