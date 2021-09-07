#include <stdio.h>
#include <unistd.h>
#include "minishell.h"


int	env(char **envp)
{
	int	env_i;

	env_i = 0;
	while (envp[env_i])
		printf("%s\n", envp[env_i++]);
	return (0);
}

int	pwd()
{
	char cwd_buffer[4096];

	getcwd(cwd_buffer, 4096);
	printf("%s\n", cwd_buffer);
	return (0);
}

/*
**[x]	env
**[x]	pwd
**[x]	echo [-n]
**[x]	cd
**[]	export
**[]	unset
*/

int	echo(char *str, char flag)
{
	printf("%s%c", str, flag);
	return (0);
}

int	cd(char *path)
{
	return (chdir(path));
}

int	parse_env(char	**envp)
{
	int	ptr_i;
	int	str_i;

	ptr_i = 0;
	while (envp[ptr_i])
	{
		str_i = 0;
		while (envp[ptr_i][str_i] || envp[ptr_i][str_i] != '=')
			++str_i;
		if (envp[ptr_i][str_i] == '=')
			envp[ptr_i][str_i] = '\0';
		++ptr_i;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{

}
