# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 14:14:04 by taretiuk          #+#    #+#              #
#    Updated: 2024/05/12 12:47:29 by taretiuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG	= pipex
LIBFT	= ./libft/libft.a

SRCS 	= src/main.c src/processes.c src/execute.c src/find_path.c src/free_2d_array.c
OBJS 	= ${SRCS:.c=.o}
MAIN	= src/main.c

HEADER	= -I include

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -g

all: 		${PROG}

%.o: %.c
	@echo "\033[33m----Compiling ${@}----"
	@$(CC) ${CFLAGS} ${HEADER} -c $< -o $@

${PROG}:	${OBJS} ${LIBFT}
					@echo "\033[33m----Compiling pipex binary----"
					@$(CC) ${OBJS} -Llibft -lft -o ${PROG}

${LIBFT}:
					@make -C ./libft

clean:
					@make clean -C ./libft
					@rm -f ${OBJS}

fclean: 	clean
					@make fclean -C ./libft
					@rm -f ${PROG}

re:			fclean all

.PHONY: all clean fclean re
