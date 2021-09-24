#include "../includes/minishell.h"

//wrap execve to find path of binary or shell file

char
	**path_list(char **envp)
{
	char	*raw_str;
	int		i;
	int		count;
	char	**path_list;

	raw_str = getenv("PATH");
	i = -1;
	count = 0;
	while (raw_str[++i] != '\0')
	{
		if (raw_str[i] == '/')
		{
			++count;
			while (raw_str[i] != ':' && raw_str[i] != '\0')
				++i;
		}
	}
	path_list = malloc(sizeof(char *) * (count + 1));
	if (path_list == NULL)
		return (NULL);
	i = -1;
	count = -1;
	while (raw_str[++i] != '\0')
	{
		if (raw_str[i] == '/')
		{
			path_list[++count] = raw_str + i;
			while (raw_str[i] != ':' && raw_str[i] != '\0')
				++i;
			if (raw_str[i] == ':')
				raw_str[i] = '\0';
		}
	}
	path_list[++count] = NULL;
	return (path_list);
}

int
	ft_execve(int argc, char **argv, char **envp)
{
	char	**path;
	int		i;

	path = path_list(envp);
	if (!path)
		return (1);
	i = -1;
	while (path[++i] != NULL)
		printf("%s\n", path[i]);
	return (0);
}

