#include <stdio.h>
#include <unistd.h>
#include "minishell.h"


int
	env(t_env *list)
{
	while (list->next != NULL)
	{
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (0);
}

int
	pwd()
{
	char cwd_buffer[4096];

	getcwd(cwd_buffer, 4096);
	printf("%s\n", cwd_buffer);
	return (0);
}

int
	echo(char *str, char flag)
{
	printf("%s%c", str, flag);
	return (0);
}

int
	cd(char *path)
{
	return (chdir(path));
}

int
	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;

	env_list = parent_env(envp);
	env(env_list);	
}
