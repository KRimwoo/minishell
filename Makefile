# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 11:56:33 by woorikim          #+#    #+#              #
#    Updated: 2024/01/22 18:32:20 by woorikim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

## woorikim's m1
#LDFLAGS = -L /opt/homebrew/opt/readline/lib -lreadline
#CPPFLAGS = -I /opt/homebrew/opt/readline/include

# cluster's MAC
LDFLAGS = -L $(HOME)/.brew/opt/readline/lib -lreadline
CPPFLAGS = -I $(HOME)/.brew/opt/readline/include

LIBFT		= -Llibft -lft
MINI_DIR = srcs/
		
SRC_BUILTIN = builtin/builtin_echo.c builtin/builtin_pwd.c builtin/builtin_cd.c  \
		builtin/builtin_export.c builtin/builtin_unset.c builtin/builtin_env.c \
		builtin/builtin_exit.c cmd_list/cmd_memory_management.c execution/heredoc_processor.c \
		execution/mini_execution.c execution/another_cmd.c \
		execution/single_cmd.c execution/apply_redirections.c
		
SRC_PARSING = parsing/token_utils.c parsing/env_utils.c parsing/env_utils2.c parsing/do_lexical.c \
		parsing/check_heredoc.c parsing/parsing_utils.c parsing/check_quotation.c parsing/split_quotation.c \
		parsing/check_env.c parsing/split_env.c parsing/parse_by_delimiter.c parsing/do_syntax.c \
		parsing/parse_cmds.c 

SRC_UTILS = utils/utils.c utils/utils2.c 

SRC_SETTING = setting/setting_signal.c setting/setting_term.c

MINI_SRCS = main.c \
			$(SRC_BUILTIN) \
			$(SRC_PARSING) \
			$(SRC_UTILS) \
			$(SRC_SETTING)

MINI_PATH		= $(addprefix $(MINI_DIR), $(MINI_SRCS))
MINI_OBJS		= $(MINI_PATH:c=o)

all : $(NAME)

$(NAME): $(MINI_OBJS)
	@make -sC libft all
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LIBFT) $^ -o $(NAME)
	@echo "$(RED)╔═════════════════════════════════════════════════╗$(RED)"
	@echo "$(RED)║                                                 ║$(RED)"
	@echo "$(RED)║                𓂋 minishell𓂋 ✦                   ║$(RED)"
	@echo "$(RED)║               compile finished.                 ║$(RED)"
	@echo "$(RED)║                                                 ║$(RED)"
	@echo "$(RED)╚═════════════════════════════════════════════════╝$(RED)"

clean:
	@make -C libft clean
	@$(RM) $(MINI_OBJS)
	@echo "$(YELLOW)╔═══════════════════════════════════════════════╗$(YELLOW)"
	@echo "$(YELLOW)║              make clean finished.             ║$(YELLOW)"
	@echo "$(YELLOW)╚═══════════════════════════════════════════════╝$(YELLOW)"

fclean:
	@make -C libft fclean
	@make clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)╔═══════════════════════════════════════════════╗$(YELLOW)"
	@echo "$(YELLOW)║             make fclean finished.             ║$(YELLOW)"
	@echo "$(YELLOW)╚═══════════════════════════════════════════════╝$(YELLOW)"

re : fclean all

.PHONY : all clean fclean re

#COLORS
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
DEFAULT		=	\033[0m