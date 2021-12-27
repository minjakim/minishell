# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/17 20:07:46 by minjakim          #+#    #+#              #
#    Updated: 2021/12/27 18:28:11 by snpark           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

declare			=	declare_check.c\
					declare_handler.c

execute			=	builtin_cd.c\
					builtin_echo.c\
					builtin_env.c\
					builtin_exit.c\
					builtin_export.c\
					builtin_pwd.c\
					builtin_unset.c\
					mini_execve.c

expand			=	expand_cmd.c\
					expand_glob.c\
					expand_glob_argv.c\
					expand_glob_filename.c\
					expand_word.c\
					expand_word_list.c

general			=	report.c\
					dispose.c\
					signal.c

prepare			=	readline.c\
					parse_line.c\
					make_words.c\
					parse_words.c\
					make_heredoc.c\
					execute_handler.c\
					redirect_io.c\
					find_cmd.c

utility			=	utils_cpy.c\
					utils_dup.c\
					utils_etc.c\
					utils_str.c\
					utils_mem.c\
					utils_x.c

SRC				=	main.c\
					initialize.c\
					$(utility:%=utility/%)\
					$(declare:%=declare/%)\
					$(execute:%=execute/%)\
					$(expand:%=expand/%)\
					$(general:%=general/%)\
					$(prepare:%=prepare/%)\

SRCS			=	$(SRC:%=./src/%)
OBJ				=	$(SRCS:./src/%.c=./obj/%.o)
ARCH			=	$(shell uname -m)

CC				=	gcc
CPPFLAGS		=	-Wall -Werror -Wextra

ifeq ($(ARCH), x86_64)
	CPPFLAGS	+=	-arch x86_64
endif
LDFLAGS			+=	-lreadline
LDFLAGS			+=	-L./lib/readline_$(ARCH)/lib
CFLAGS			+=	-I./lib/readline_$(ARCH)/include

./obj/%.o		:	./src/%.c
	@mkdir -p $(dir ./obj/$*)
	$(CC) $(CPPFLAGS) -c $< -o $@

all 			:	$(NAME)

$(NAME)			:	$(OBJ)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJ) -o $@

clean			:
					rm -rf ./obj

fclean			:	clean
					rm -rf minishell

bonus			:	all

re				:	fclean all
