# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/17 20:07:46 by minjakim          #+#    #+#              #
#    Updated: 2021/12/20 21:42:24 by minjakim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

declare			=	declare_check.c\
					declare_edit.c\
					declare_envp.c\
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
					expand_teilde.c\
					expand_word.c

general			=	report.c\
					dispose.c\
					signal.c\
					temp.c\
					utils.c

prepare			=	readline.c\
					parse_line.c\
					make_words.c\
					parse_words.c\
					make_heredoc.c\
					execute_handler.c\
					redirect_io.c\
					find_cmd.c

SRC				=	main.c\
					initialize.c\
					$(declare:%=declare/%)\
					$(execute:%=execute/%)\
					$(expand:%=expand/%)\
					$(general:%=general/%)\
					$(prepare:%=prepare/%)

SRCS			=	$(SRC:%=./src/%)
OBJ				=	$(SRCS:./src/%.c=./obj/%.o)
ARCH			=	$(shell uname -m)

ifeq ($(ARCH), x86_64)
	CPPFLAGS	+=	-arch x86_64
endif
LDFLAGS			+=	-L./lib/readline_$(ARCH)/lib -L./lib/ncurses_$(ARCH)/lib
CPPFLAGS		+=	-I./lib/readline_$(ARCH)/include -I./lib/ncurses_$(ARCH)/include
TEMP			=	gcc -lreadline -lncurses

./obj/%.o		:	./src/%.c
	@mkdir -p $(dir ./obj/$*)
	gcc -c $< -o $@

all 			:	$(NAME)

$(NAME)			:	$(OBJ)
	$(TEMP) $(LDFLAGS) $(CPPFLAGS) $(OBJ) -o $@

clean			:
					rm -rf ./obj

fclean			:	clean
					rm -rf minishell

re				:	fclean all
