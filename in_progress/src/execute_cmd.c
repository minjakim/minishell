#iunclude "minishell.h"

int
	shell_execve(char *command, char **args, char **env)
{
	char *path;

	if(*comand == '.' || *command == '~' || *command == '\')
		execve(command, args, env);
	else //only file name maybe...
	{
		getenv("PATH");
		//parsing a path
		//
		
	}
}
