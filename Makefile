NAME=minishell

builtin_function=cd.c\
				 echo.c\
				 env.c\
				 exit.c\
				 export.c\
				 ms_getenv.c\
				 pwd.c\
				 unset.c

execute=$(builtin_function:%=builtins/%)\
	execute_cmd.c\
	ft_execve.c

readline=
input=$(readline:%=readline/%)
parse=parse_env.c
redirection=redirect.c

SRC=shell.c\
	$(execute:%=execute/%)\
	$(input:%=input/%)\
	$(parse:%=parse/%)\
	$(redirection:%=redirection/%)

SRCS=$(SRC:%=./src/%)
OBJ=$(SRCS:%.c=%.o)

CPPFLAG= -Wall -Werror -Wextra

%.o:%.c
	gcc $(CPPFLAG) -c $< -o $@

#$(OBJ):$(SRCS)
#	gcc $(CPPFLAG) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	gcc -lreadline -lncurses -L./lib/readline_arm64/lib -I./lib/readline_arm64/include $(CPPFLAG) $(OBJ) -o $@

clean :
	rm -rf $(OBJ)
