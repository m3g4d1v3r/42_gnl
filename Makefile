SRCS	= get_next_line.c \
		  get_next_line_utils.c
OBJS	= ${SRCS:.c=.o}
INCD	= ./
NAME	= libft.a

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Werror -Wextra -D BUFFER_SIZE=42

%.o:		${SRCS}%.c
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS} ${BOBJS}

fclean:		clean
			${RM} ${NAME}
			${RM} simple0.txt
			${RM} simple1.txt
			${RM} gnl_test.out

re:			fclean all

.PHONY:		all clean fclean re

test:		${NAME}
			gcc -L./ test_src/get_next_line.c -lcriterion -lpthread -lft -o gnl_test.out
