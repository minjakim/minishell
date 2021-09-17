#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

t_env	*env_list;

int
	env(t_env *list)
{
	while (list != NULL)
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
	export(const char *key)
{
	t_env	*tmp;
	t_env	*pre;

	tmp = env_list;
	pre = NULL;
	while (tmp && strcmp(tmp->key, key) && tmp->next)
	{
		pre = tmp;
		tmp = tmp->next;
	}
	if (tmp && !strcmp(tmp->key, key))
	{
		free(tmp->key);
		free(tmp->value);
		pre->next = tmp->next;
		free(tmp);
	}
	return (0);
}
int
	main(int argc, char **argv, char **envp)
{
	char	*test;

	env_list = parent_env(envp);
	env(env_list);
	test = strdup("test=123");
	env_list = update_env(test, env_list, 0);
	env(env_list);	
	free(test);
	test = strdup("test=qwerty");
	env_list = update_env(test, env_list, 0);
	env(env_list);	
	export("test");
	env(env_list);	
}
