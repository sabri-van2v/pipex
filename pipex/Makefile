SRC = 	main.c path.c error.c here_doc.c many_pipes.c

SRCS = 	${addprefix srcs/, ${SRC}}

OBJ = 	${addprefix binaries/, ${SRC}}

OBJS = 	${OBJ:%.c=%.o}

NAME = 	pipex

MAKELIB = @make -C Libft

MAKEBIN = @mkdir -p binaries/

MAKEFLAGS += --no-print-directory 

CC 	= 	cc

RM 	= 	rm -f

CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = Libft/includes/gnl Libft/includes/libc Libft/includes/ptf includes/

HEADER = includes/pipex.h

binaries/%.o: srcs/%.c ${HEADER} libft | binaries
	${CC} ${CFLAGS} -c $< -o $@ ${addprefix -I, ${INCLUDES}}

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${OBJS} -LLibft -lft

all: ${NAME}

libft:
	${MAKELIB}

binaries:
	${MAKEBIN}

bonus: all

clean:
	 ${RM} -r binaries
	 make clean -C Libft

fclean: clean
	 ${RM} ${NAME}
	 make fclean -C Libft

re: fclean all

.PHONY:	all bonus clean fclean re