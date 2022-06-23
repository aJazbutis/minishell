# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 20:29:40 by ajazbuti          #+#    #+#              #
#    Updated: 2022/06/22 23:31:42 by ajazbuti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

SRC = minishell.c utils.c utils1.c env.c env_var.c ft_env_to_tab.c\
          ft_cd.c ft_env.c ft_export.c ft_export_utils.c  ft_unset.c\
          ft_add_env_var.c ft_echo.c ft_exit.c ft_pwd.c\
          cmd_lst.c flst.c\
          ft_exec.c ft_exec_utils.c ft_exec_cmd.c ft_exec_exe.c\
          ft_heredoc.c ft_heredoc_utils.c ft_heredoc_exp_utils.c\
		  ft_fds.c ft_redir.c\
          ft_pipeless.c ft_route.c ft_minor_expnd.c\
          sigs.c\
          lexer.c lexer_tokens_utils.c lexer_string_utils.c lexer_uni_utils.c\
          lexer_uni_utils2.c lexer_exp_utils.c lexer_error_utils.c lexer_uni_utils3.c\
          parser.c parser_utils.c\

SRC_D = ./sources/

OBJ = ${SRC:.c=.o}

LIBFT_D = ./libft/

LIBFT = ${LIBFT_D}libft.a

LIBRL = ${HOME}/goinfre/.brew/opt/readline/lib

INC = -I./includes -I${LIBFT_D}/includes -I${HOME}/goinfre/.brew/opt/readline/include

LIBS = -L${LIBFT_D} -lft -L${LIBRL}

all: ${NAME}

%.o: ${SRC_D}%.c
	@${CC} ${CFLAGS} ${INC} -c $^

#%.o: ${SRC_D}%.c
#	@${CC} ${CFLAGS} -I./libft/includes -I./includes -L./libft/ -lft -c $^

${NAME}: ${OBJ_D} ${LIBFT_D} ${LIBFT} ${OBJ}
	@${CC} ${LIBS} ${OBJ} -lreadline -o ${NAME}
	@echo "\033[1;35mOur wonderful minishell has been compiled!\033[1;0m\033[0m"

#${NAME}: ${OBJ_D} ${LIBFT_D} ${LIBFT} ${OBJ}
#	@${CC} ${LIBS} ${OBJ} -lreadline -I./libft/includes -I./includes -L./libft/ -lft -o ${NAME}
#	@echo "\033[1;35mOur wonderful minishell has been compiled!\033[1;0m\033[0m"


${LIBFT}:
	@make -C ${LIBFT_D} -silent
	@echo "\033[1;35mLibft has been created!\033[1;0m\033[0m"

clean:
	@${RM} ${OBJ}
	@make -C ${LIBFT_D} -silent clean
	@echo "\033[1;35m*.o files have been removed.\033[1;0m\033[0m"

fclean: clean
	@${RM} ${NAME}
	@make -C ${LIBFT_D} -silent fclean
	@echo "\033[1;35mCleaning is done.\033[1;0m\033[0m"

re: fclean all

norm:
	norminette $(SRC_D) includes/*.h libft

.PHONY: all clean fclean re
