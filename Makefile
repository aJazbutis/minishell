# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 18:13:18 by ajazbuti          #+#    #+#              #
#    Updated: 2022/05/10 22:17:10 by ajazbuti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

SRC = minishell.c utils1.c ft_cd.c env.c env_var.c ft_env.c ft_export.c\
	  ft_add_env_var.c ft_echo.c ft_execute_executable.c ft_exit.c\
	  ft_run_cmd.c

SRC_D = ./sources/

#OBJ_D = ./obj/

OBJ = ${SRC:.c=.o}

LIBFT_D = ../../libft_42/

LIBFT = ${LIBFT_D}libft.a

LIBRL = ${HOME}/goinfre/.brew/opt/readline/lib

INC = -I./includes -I${LIBFT_D}includes -I${HOME}/goinfre/.brew/opt/readline/include

LIBS = -L${LIBFT_D} -lft -L${LIBRL}

all: ${NAME}

%.o: ${SRC_D}%.c
	${CC} ${CFLAGS} ${INC} -c $^

${NAME}: ${OBJ_D} ${LIBFT_D}/sources ${LIBFT} ${OBJ}
	${CC} ${LIBS} ${OBJ} -lreadline -o ${NAME}

${LIBFT}:
	make -C ${LIBFT_D}

clean:
	${RM} ${OBJ}
	make -C ${LIBFT_D} clean

fclean: clean
	${RM} ${NAME}
	make -C ${LIBFT_D} fclean

re: fclean all

.PHONY: all clean fclean re
