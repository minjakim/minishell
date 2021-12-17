/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:58:20 by snpark            #+#    #+#             */
/*   Updated: 2021/12/17 21:04:30 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	is_builtin(const char *str)
{
	if (!str || !*str || *str == ':')
		return (FT_NULL);
	else if (*str == 'c' && str[1] == 'd' && str[2] == '\0')
		return (FT_CD);
	else if (*str == 'e')
	{
		if (str[1] == 'c' && ft_strcmp(str + 2, "ho") == 0)
			return (FT_ECHO);
		else if (str[1] == 'n' && ft_strcmp(str + 2, "v") == 0)
			return (FT_ENV);
		else if (str[1] == 'x' && ft_strcmp(str + 2, "it") == 0)
			return (FT_EXIT);
		else if (str[1] == 'x' && ft_strcmp(str + 2, "port") == 0)
			return (FT_EXPORT);
	}
	else if (*str == 'p' && str[1] == 'w' && str[2] == 'd' && str[3] == '\0')
		return (FT_PWD);
	else if (*str == 'u' && ft_strcmp(str + 1, "nset") == 0)
		return (FT_UNSET);
	return (MINI_EXECVE);
}

static char
	*get_next_path_element(char *string, int *p_index)
{
	int		i;
	int		start;
	char	*path;

	if (string == NULL)
		return (NULL);
	if (*p_index >= ft_strlen(string))
		return (NULL);
	i = *p_index;
	if (i > 0 && string[i] == ':')
		++i;
	start = i;
	while (string[i] && string[i] != ':')
		++i;
	*p_index = i;
	if (start == i)
	{
		if (string[i])
			++(*p_index);
		path = ft_strdup(".");
	}
	else
		path = ft_strndup(string + start, i - start);
	return (path);
}

static char
	*find_in_path_element(char *name, char *path)
{
	char		*full_path;
	const int	full_path_len = ft_strlen(path) + ft_strlen(path) + 2;
	struct stat	finfo;

	full_path = xcalloc(sizeof(char) * full_path_len);
	ft_strcat(ft_strcat(strcpy(full_path, path), "/"), name);
	if (stat(full_path, &finfo) < 0)
	{
		free(full_path);
		return (NULL);
	}
	if (finfo.st_mode & S_IFDIR)
		return (NULL);
	return (full_path);
}

int
	command_find_in_path(t_command *command)
{
	char	*path_list;
	char	*path;
	int		path_index;

	path_list = getenv("PATH");
	path_index = 0;
	while (path_list && path_list[path_index])
	{
		path = get_next_path_element(path_list, &path_index);
		if (path == NULL)
			break ;
		command->path = find_in_path_element(command->argv[0], path);
		free(path);
		path = NULL;
		if (command->path != NULL)
			return (0);
	}
	if (!path_list || !*path_list || !command->path)
		return (127);
	return (0);
}

int
	command_find(t_command *command)
{
	const char	*name = command->argv[0];
	struct stat	buf;

	if (!name)
		return (0);
	if (ft_strchr(name, '/') != NULL && stat(name, &buf) == 0)
		command->path = ft_strdup(name);
	else if (is_builtin(name))
		command->flags |= CMD_COMMAND_BUILTIN;
	else
		return (command_find_in_path(command));
	return (0);
}
