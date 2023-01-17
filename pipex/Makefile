SRC = 	main.c path.c error.c

#SRC_BONUS =	main.c

SRCS = 	${addprefix srcs/, ${SRC}}

#SRCS_BONUS = ${addprefix bonus/, ${SRC_BONUS}}

OBJ = 	${addprefix binaries/, ${SRC}}

OBJS = 	${OBJ:%.c=%.o}

#OBJ_BONUS =	${addprefix binaries/, ${SRC_BONUS}}

#OBJS_BONUS = ${OBJ_BONUS:%.c=%.o}

NAME = 	pipex

#NAME_BONUS = checker

MAKELIB = @make -C Libft

MAKEBIN = @mkdir -p binaries/

MAKEFLAGS += --no-print-directory 

CC 	= 	cc

RM 	= 	rm -f

CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = Libft/includes/gnl Libft/includes/libc Libft/includes/ptf includes/

HEADER = includes/pipex.h

#HEADER_BONUS = includes/push_swap_bonus.h

binaries/%.o: srcs/%.c ${HEADER} Libft/libft.a | binaries
	${CC} ${CFLAGS} -c $< -o $@ ${addprefix -I, ${INCLUDES}}

#binaries/%.o: bonus/%.c ${HEADER_BONUS} Libft/libft.a | binaries
#	${MAKEBIN}
#	${CC} ${CFLAGS} -c $< -o $@ ${addprefix -I, ${INCLUDES}}

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${OBJS} -LLibft -lft

#${NAME_BONUS}: ${OBJS_BONUS}
#	${CC} -o ${NAME_BONUS} ${OBJS_BONUS} -LLibft -lft

all: ${NAME}

Libft/libft.a:
	${MAKELIB}

binaries:
	${MAKEBIN}

#bonus: ${NAME_BONUS}

clean:
	 ${RM} -r binaries
	 make clean -C Libft

fclean: clean
	 ${RM} ${NAME}
	 make fclean -C Libft

re: fclean all

.PHONY:	all bonus clean fclean re