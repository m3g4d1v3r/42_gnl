SRCS	= get_next_line.c \
		  get_next_line_utils.c
OBJS	= ${SRCS:.c=.o}
INCD	= ./
NAME	= libft.a

CC		= gcc
RM		= rm -f

CFLAGS	= -g -Wall -Werror -Wextra -D BUFFER_SIZE=42

%.o:		${SRCS}
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS} ${BOBJS} bonus

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re

test:		${NAME}
			g++ -L./ gnl_test.cpp -lft -lgtest -lpthread -o gnl_test.out
			./gnl_test.out && rm gnl_test.out
