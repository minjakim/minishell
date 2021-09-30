#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>

//pid_t
# include <sys/types.h>

//ARG_MAX
# include <limits.h>
//strdup
# include <string.h>

typedef struct	s_command t_command;

typedef struct s_file
{
	char	*file;
	char	redirection;
}				t_file;

typedef struct	s_command
{
	char	**argv;
	int		stream_out;
	int		stream_in;
	t_file	*out_file;
	t_file	*in_file;
	int		pipe;
	t_command	*next;
}				t_command;

int parse_env(char ***original_envp);

int	shell_execve(char *command, char **args, char **env);

int ft_execve(char **argv, char **envp);

int	redirect(char **argv, char **envp);
#endif
