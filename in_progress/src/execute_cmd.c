#include "../includes/minishell.h"

int
	shell_execve(char *command, char **args, char **env)
{
	char *path;

	if(*command == '.' || *command == '~' || *command == '/')
		execve(command, args, env);
	else
		ft_execve(args, env);
	return (0);
}
