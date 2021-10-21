/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 13:05:17 by snpark            #+#    #+#             */
/*   Updated: 2021/10/21 15:41:03 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//wrap execve to find path of binary or shell file

char
	**path_list(char **envp)
{
	char			*raw_str;
	int				i;
	int				count;
	char			**path_list;
	t_key_value_idx	idx;

	idx = ms_getenv("PATH", envp);
	raw_str = strdup(envp[idx.key]);
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
	path_list[count] = NULL;
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

int
	ms_opendir(DIR **dir_pointer, char *path)
{
	if (path == NULL)
		return (0);
	*dir_pointer = opendir(path);
	if (*dir_pointer == NULL)
		return (0);
	return (1);
}

int
	ms_readdir(struct dirent **dirinfo, DIR *dir_pointer)
{
	*dirinfo = readdir(dir_pointer);
	if (*dirinfo == NULL)
		return (0);
	return (1);
}

char
	*return_path(char **path, char *command)
{
	DIR				*dir_pointer;
	struct dirent	*dirinfo;
	int				i;
	int				tmp;

	i = -1;
	while (ms_opendir(&dir_pointer, path[++i]))
	{
		if (dir_pointer == NULL)
			return (NULL);
		while (ms_readdir(&dirinfo, dir_pointer))
		{
			if (!strcmp(command, dirinfo->d_name))
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
	if (path == NULL)
		exit(1);
	command = return_path(path, argv[0]);
	free(path);
	execve(command, argv, envp);
	return (0);
}
