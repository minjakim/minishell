NAME=minishell

declare=declare_check.c\
		declare_edit.c\
		declare_envp.c\
		declare_handler.c

execute=builtin_cd.c\
		builtin_echo.c\
		builtin_env.c\
		builtin_exit.c\
		builtin_export.c\
		builtin_pwd.c\
		builtin_unset.c\
		mini_execve.c

expand=expand_command.c\
	   expand_glob.c\
	   expand_teilde.c\
	   expand_word.c

general=exception.c\
		signal.c\
		temp.c\
		utils.c

prepare=command_clean.c\
		command_execute.c\
		command_find.c\
		command_handler.c\
		command_io.c\
		command_redirect.c\
		command_heredoc.c\
		word_list_handler.c\
		word_list_flag.c

SRC=main.c\
	initialize.c\
	$(declare:%=declare/%)\
	$(execute:%=execute/%)\
	$(expand:%=expand/%)\
	$(general:%=general/%)\
	$(prepare:%=prepare/%)

SRCS=$(SRC:%=./src/%)

OBJ=$(SRCS:%.c=%.o)

ARCH=$(shell uname -m)
readline=-lreadline -lncurses -L./lib/readline_$(ARCH)/lib -I./lib/readline_$(ARCH)/include

ifeq ($(ARCH), x86_64)
	CPPFLAGS=-arch x86_64
endif

%.o		: %.c
	gcc $(CPPFLAGS) $(readline) -c $< -o $@

all 	: $(NAME)

$(NAME) : $(OBJ)
	gcc $(CPPFLAGS) $(readline) $(OBJ) -o $@

clean	:
	rm -rf $(OBJ)

fclean	: clean
	rm minishell

re		: fclean all

