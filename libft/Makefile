# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 07:00:06 by alevasse          #+#    #+#              #
#    Updated: 2022/08/26 10:18:56 by alevasse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= libft.a

FILES			= gnl/get_next_line.c gnl/get_next_line_utils.c is/ft_isalnum.c is/ft_isalpha.c \
					is/ft_isascii.c is/ft_isdigit.c is/ft_isprint.c lst/ft_lstadd_back.c \
					lst/ft_lstadd_front.c lst/ft_lstclear.c lst/ft_lstlast.c lst/ft_lstnew.c \
					lst/ft_lstsize.c mem/ft_bzero.c mem/ft_calloc.c mem/ft_memalloc.c mem/ft_realloc.c \
					mem/ft_memchr.c mem/ft_memcmp.c mem/ft_memcpy.c mem/ft_memmove.c mem/ft_free_tab.c \
					mem/ft_free_n_tab.c mem/ft_memset.c printf/ft_add_flags.c printf/ft_conv_char.c \
					printf/ft_conv_hex.c printf/ft_conv_int.c printf/ft_conv_ptr.c printf/ft_conv_str.c \
					printf/ft_conv_uint.c printf/ft_define_args.c printf/ft_get_opts.c printf/ft_printf.c \
					put/ft_put_size.c put/ft_putchar_fd.c put/ft_putchar.c put/ft_putstr_fd.c \
					put/ft_putstr.c put/ft_putnbr_fd.c put/ft_putnbr.c put/ft_putendl_fd.c \
					put/ft_putendl.c put/ft_putnbr_base.c to/ft_atoi.c to/ft_atol.c to/ft_itoa.c \
					to/ft_itoa_hex.c to/ft_itoa_ptr.c to/ft_itoa_unsigned.c to/ft_tolower.c \
					to/ft_toupper.c str/ft_insert_str.c str/ft_split.c str/ft_strcat.c \
					str/ft_strchr.c str/ft_strcmp.c str/ft_strcpy.c str/ft_strdel.c \
					str/ft_strdup.c str/ft_striteri.c str/ft_strjoin.c str/ft_strlcat.c \
					str/ft_strlcpy.c str/ft_strlen.c str/ft_strmapi.c str/ft_strncat.c \
					str/ft_strncmp.c str/ft_strncpy.c str/ft_strnew.c str/ft_strnstr.c \
					str/ft_strrchr.c str/ft_strstr.c str/ft_strtrim.c str/ft_substr.c \
					is/ft_isspace.c

DIR_SRC 		= src
DIR_OBJ 		= obj
SUB_DIR 		= gnl is lst mem printf put str to

SRC 			= ${foreach dir, ${FILES}, 	${addprefix ${DIR_SRC}/, ${dir}}}
OBJ_DIR 		= ${foreach dir, ${SUB_DIR}, ${addprefix ${DIR_OBJ}/, ${dir}}}
OBJ 			= ${subst ${DIR_SRC}, ${DIR_OBJ}, ${SRC:.c=.o}}

INCLUDE 		= -I./../include

CC 				= gcc -g
CFLAGS 			= -Wall -Wextra -Werror

AR 				= ar rcs
RM 				= rm -f

REC 			= -r

GREEN			:= "\033[0;32m"
CYAN			:= "\033[0;36m"
RESET			:= "\033[0m"

${DIR_OBJ}/%.o:	${DIR_SRC}/%.c
				@mkdir -p ${DIR_OBJ} ${OBJ_DIR}
				@${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${@:.c=.o}

${NAME}: 		${OBJ}
				@${AR} ${NAME} ${OBJ}
				@echo ${GREEN}"Compiled '${NAME}' with success" ${RESET}

all: 			${NAME}

clean:
				@${RM} ${OBJ}
				@echo ${CYAN}"Cleaned 'libft' objects with success"${RESET}
				@${RM} ${REC} ${DIR_OBJ}
				@echo ${CYAN}"Cleaned '${DIR_OBJ}' 'libft' with success"${RESET}

fclean:
				@${RM} ${NAME}
				@echo ${CYAN}"Removed '${NAME}' with success"${RESET}

re: 			fclean all

.PHONY: 		all clean fclean re
