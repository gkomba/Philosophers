NAME = philo
SRCS = ph_main.c\
	ph_utils.c\
	ph_actions.c\
	ph_threads.c\
	ph_mutexes.c\
	ph_monitor.c\
	ph_init.c\
	ph_time.c\
	ph_inform.c\
	ph_check.c\

OBJS = ${SRCS:.c=.o}
DTRCF = -fsanitize=thread -fsanitize=undefined -g
CC = cc
CFLGS = -Wall -Wextra -Werror
RM = rm -f

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLGS} -o ${NAME} ${OBJS}

%.o: %.c
	${CC} ${CFLGS} -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
