NAME=minishell

SRC=shell.c\
	parse_env.c\
	ft_execve.c\
	execute_cmd.c

SRCS=$(SRC:%=./src/%)
OBJ=$(SRCS:%.c=%.o)

CPPFLAG= -Wall -Werror -Wextra

rl= -l readline

%.o:./src/%.c
	gcc $(CPPFLAG) $(rl) $> -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(CPPFLAG) $(rl) $(OBJ) -o $@
