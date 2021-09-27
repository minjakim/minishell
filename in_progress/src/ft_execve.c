#include "../includes/minishell.h"

//wrap execve to find path of binary or shell file

char
	**path_list(char **envp)
{
	char	*raw_str;
	int		i;
	int		count;
	char	**path_list;

	(void)envp;
	raw_str = getenv("PATH");//maybe I need to change this
	raw_str = strdup(raw_str);
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

char
	*cat_path(char *path, char *command)
{
	char	*abs_path;
	int		i;
	int		len;

	len = strlen(path) + strlen(command) + 2;
	abs_path = malloc(sizeof(char) * len);
	if (!abs_path)
		return (NULL);
	i = -1;
	while (path[++i] != '\0')
		abs_path[i] = path[i];
	abs_path[i] = '/';
	while (*command)
		abs_path[++i] = *command++;
	abs_path[++i] = '\0';
	return (abs_path);
}

char
	*return_path(char **path, char *command)
{
	DIR				*dir_pointer;
	struct dirent	*dirinfo;
	int				i;

	i = -1;
	while ((dir_pointer = opendir(path[++i])))
	{
		if (dir_pointer == NULL)
			return (NULL);
		while ((dirinfo = readdir(dir_pointer)))
		{
			if(!strcmp(command, dirinfo->d_name))
				return (cat_path(path[i], command));
		}
		if (closedir(dir_pointer))
			return (NULL);
	}
	return (NULL);
}

int
	ft_execve(char **argv, char **envp)
{
	char	**path;
	char	*command;

	path = path_list(envp);
	if (!path)
		return (1);
	command = return_path(path, argv[0]);
	execve(command, argv, envp);
	return (0);
}

