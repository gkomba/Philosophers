# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkomba <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 15:51:45 by gkomba            #+#    #+#              #
#    Updated: 2024/09/06 13:18:23 by gkomba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = ph_main.c\
	ph_utils.c\
	ph_actions.c\
	ph_threads.c\
	ph_mutexes.c

OBJS = ${SRCS:.c=.o}
CFLGS = -Wall -Wextra -Werror
DTRCF = -fsanitize=thread -g
CC = cc
RM = rm -f

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLGS} ${DTRCF} -o ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
