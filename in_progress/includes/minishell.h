#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

//ARG_MAX
# include <limits.h>
//strdup
# include <string.h>

int parse_env(char ***original_envp);

int ft_execve(char **argv, char **envp);

#endif
