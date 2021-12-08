/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:58:20 by snpark            #+#    #+#             */
/*   Updated: 2021/12/08 14:53:05 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <string.h>

char
	*get_next_path_element(char *string, int *p_index)
{
	int		i;
	int		start;
	char	*path;

	if (string == NULL)
		return (NULL);
	if (*p_index >= strlen(string))
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
		path = strdup(".");
	}
	else
		path = strndup(string + start, i);
	return (path);
}

char
	*find_in_path_element(char *name, char *path)
{
	char		*full_path;
	struct stat	finfo;
	
	full_path = malloc(sizeof(char) * (strlen(name) + strlen(path) + 2));
	if (full_path == NULL)
		return (NULL);
	memset(full_path, 0, strlen(name) + strlen(path) + 2);
	strcat(strcat(strcpy(full_path, path), "/"), name); 
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
	is_builtin(const char *str)
{
	if (!str || !*str || *str == ':')
		return (8);
	else if (*str == 'c' && str[1] == 'd' && str[2] == '\0')
		return (1);
	else if (*str == 'e')
	{
		if (str[1] == 'c' && strcmp(str + 2, "ho") == 0)
			return (2);
		else if (str[1] == 'n' && strcmp(str + 2, "v") == 0)
			return (3);
		else if (str[1] == 'x' && strcmp(str + 2, "it") == 0)
			return (4);
		else if (str[1] == 'x' && strcmp(str + 2, "port") == 0)
			return (5);
	}
	else if (*str == 'p' && str[1] == 'w' && str[2] == 'd' && str[3] == '\0')
		return (6);
	else if (*str == 'u' && strcmp(str + 1, "nset") == 0)
		return (7);
	return (0);
}

int
	find_in_path_command(t_shell *mini)
{
	char		*path_list;
	char		*path;
	int			path_index;

	path_list = getenv("PATH");
	path_index = 0;
	while (path_list && path_list[path_index])
	{
		path = get_next_path_element(path_list, &path_index);
		if (path == NULL)
			break ;
		mini->cmd->value.simple.path = find_in_path_element(\
				mini->cmd->value.simple.argv[0], path); 
		free(path);
		if (mini->cmd->value.simple.path != NULL)
			return (0);
	}
	if (!path_list || !*path_list || !mini->cmd->value.simple.path)
		return (127);// no such file of directory
	return (0);
}

int
	find_cmd(t_shell *mini)
{
	const char	*name = mini->cmd->value.simple.argv[0];

	if (strchr(name, '/') != NULL && stat(name, NULL) == 0)
		mini->cmd->value.simple.path = strdup(name);
	else if (is_builtin(name))
		mini->cmd->flags |= CMD_COMMAND_BUILTIN;
	else
		return (find_in_path_command(mini));
	return (0);
}
