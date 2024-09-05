# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkomba <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 15:51:45 by gkomba            #+#    #+#              #
#    Updated: 2024/09/05 13:54:09 by gkomba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = ph_main.c
OBJS = ${SRCS:.c=.o}
CFLGS = -Wall -Wextra -Werror
DTRCF = -fsanitize=thread -g
CC = cc
RM = rm -f
LIBFT = libft

all: ${NAME}

${NAME}: ${OBJS}
	make -C ${LIBFT}
	${CC} ${CFLGS} ${DTRCF} -o ${NAME} ${OBJS} ${LIBFT}/libft.a

clean:
	make clean -C ${LIBFT}
	${RM} ${OBJS}

fclean: clean
	make fclean -C ${LIBFT}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
