NAME=minishell

builtin_function=mini_env.c\
				 mini_export.c\
				 mini_unset.c\
				 mini_pwd.c\
				 mini_cd.c\
				 mini_echo.c\
				 mini_exit.c

execute=$(builtin_function:%=builtins/%)\
	execute_cmd.c\
	expand_cmd.c\
	find_cmd.c\
	ft_execve.c\
	redirect.c
#	ft_execve.c

readline=
input=$(readline:%=readline/%)
parse=parse_envp.c\
	  make_cmd.c\
	  parse_line.c
redirection=redirect.c
declare=declare.c\
		general.c\
		make_envp.c\
		edit_declare_value.c

SRC=../main.c\
	initialize.c\
	minishell.c\
	$(parse:%=parse/%)\
	$(execute:%=execute/%)\
	$(declare:%=declare/%)
#	shell.c\
#	$(input:%=input/%)\
#	$(redirection:%=redirection/%)

SRCS=$(SRC:%=./src/%)
OBJ=$(SRCS:%.c=%.o)

#CPPFLAG= -Wall -Werror -Wextra

%.o:%.c
	gcc $(CPPFLAG) -c $< -o $@

#$(OBJ):$(SRCS)
#	gcc $(CPPFLAG) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	gcc -lreadline -lncurses -L./lib/readline_arm64/lib -I./lib/readline_arm64/include $(CPPFLAG) $(OBJ) -o $@

clean :
	rm -rf $(OBJ)
