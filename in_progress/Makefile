NAME=minishell

SRC=shell.c\
	parse_env.c\
	ft_execve.c\
	execute_cmd.c\
	redirect.c\
	echo.c\
	cd.c\
	pwd.c\
	export.c\
	ms_getenv.c

SRCS=$(SRC:%=./src/%)
OBJ=$(SRCS:%.c=%.o)

CPPFLAG= -Wall -Werror -Wextra

rl= -l readline

%.o:%.c
	gcc $(CPPFLAG) -c $< -o $@

#$(OBJ):$(SRCS)
#	gcc $(CPPFLAG) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(CPPFLAG) $(rl) $(OBJ) -o $@

clean :
	rm -rf $(OBJ)
