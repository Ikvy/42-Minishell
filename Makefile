NAME			= minishell

SRC				=	src/main.c	src/close.c \
					src/lexer/lexer.c src/lexer/lexer_utils.c src/lexer/token_list.c src/lexer/parenthesis.c \
					src/builtins/echo.c src/builtins/pwd.c src/builtins/env.c src/builtins/cd.c \
					src/builtins/export.c src/builtins/unset.c src/builtins/exit.c \
					src/parser/parse.c src/parser/parse_node.c src/parser/parse_utils.c \
					src/executor/executor.c src/executor/path.c

SRC_B			= 

OBJ				= ${SRC:.c=.o}
OBJ_B			= ${SRC_B:.c=.o}

INCLUDE 		= -I./include/ 

RL              = -L/usr/local/Cellar/readline/8.1.2/lib -lreadline

HEAD			= include/libft.h

LIBS 			= ./libft/

CC 				= gcc -g
CFLAGS 			= -Wall -Wextra -Werror #-fsanitize=address

AR 				= ar rcs
RM 				= rm -f

GREEN			:= "\033[0;32m"
CYAN			:= "\033[0;36m"
RESET			:= "\033[0m"

%.o:			%.c
				@${CC} ${CFLAGS} ${INCLUDE} -o $@ -c $<

all: 			${NAME}

bonus:			${OBJ_B} ${HEAD}
				@make all -C ${LIBS}
				@echo ${GREEN}"Successfully updated 'libft'" ${RESET}
				@${CC} ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJ_B} ${LIBS}libft.a
				@echo ${GREEN}"Compiled '${NAME}' with success" ${RESET}
				@touch bonus

${NAME}:		${OBJ} ${HEAD}
				@make all -C ${LIBS}
				@echo ${GREEN}"Successfully updated 'libft'" ${RESET}
				@${CC} ${RL} ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJ} ${LIBS}libft.a
				@echo ${GREEN}"Compiled '${NAME}' with success" ${RESET}

clean:
				@make clean -C ${LIBS}
				@${RM} ${OBJ} ${OBJ_B}
				@echo ${CYAN}"Cleaned '${NAME}' objects with success"${RESET}
				
fclean:			clean
				@make fclean -C ${LIBS}
				@${RM} ${NAME} ${NAME_B}
				@echo ${CYAN}"Removed '${NAME}' with success"${RESET}

re:				fclean all

.PHONY: 		all clean fclean re
