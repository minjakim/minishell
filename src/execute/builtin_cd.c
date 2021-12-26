/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:03:50 by snpark            #+#    #+#             */
/*   Updated: 2021/12/26 14:42:01 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_str
	*get_t_str(const char *const str)
{
	t_str	*ptr;

	ptr = xcalloc(sizeof(t_str *));
	ptr->str = ft_strdup(str);
	ptr->len = ft_strlen(str);
	return (ptr);
}

void
	declare_update_node(const char *const key, const char *const value)
{
	t_declare	*node;
	char		*line;
	t_str		*get_key;
	t_str		*get_value;

	node = declare_search(key);
	if (node)
	{
		if (node->type != K_ONLY)
			disposer(node->value.str, node->line, NULL, NULL);
		node->value.str = ft_strdup(value);
		node->value.len = ft_strlen(node->value.str);
		node->line = declare_new_line(&node->key, &node->value);
	}
	else
	{
		get_key = get_t_str(key);
		get_value = get_t_str(value);
		line = declare_new_line(get_key, get_value);
		if (declare_add(line)->type == EXPORT)
			++g_status.env.envc;
		disposer(get_key->str, get_key, get_value->str, get_value);
		xfree(line);
	}
	g_status.env.edited = TRUE;
}

static int
	set_path(char *const from)
{
	char *const	path = getcwd(NULL, 0);

	if (path == NULL)
	{
		xfree(from);
		return (ERROR);
	}
	declare_update_node(PWD, path);
	declare_update_node(OLDPWD, from);
	declare_update_envp();
	disposer(path, from, NULL, NULL);
	return (OK);
}

static const char
	*get_path(const char *const *const argv)
{
	char	*path;

	if (argv[1] == NULL)
	{
		path = declare_get_value(HOME);
		if (!path)
			report_exception(argv[0], NULL, EX_CD_HOME, GENERAL_ERROR);
		return (path);
	}
	else if (argv[1][0] == '-' && argv[1][1] == '\0')
	{
		path = declare_get_value(OLDPWD);
		if (!path)
			report_exception(argv[0], NULL, EX_CD_OLDPWD, GENERAL_ERROR);
		else
			printf("%s\n", path);
		return (path);
	}
	else
		return (argv[1]);
}

int
	builtin_cd(const t_command *const cmd)
{
	const char *const	dest = \
		get_path((const char *const *const)cmd->argv);
	char				*from;

	if (dest == NULL)
		return (g_status.exit = GENERAL_ERROR);
	from = getcwd(NULL, 0);
	if (from == NULL)
		return (report_error(cmd->argv[0], NULL, errno));
	if (chdir(dest) == ERROR)
	{
		xfree(from);
		return (report_error(cmd->argv[0], dest, errno));
	}
	if (set_path(from) == ERROR)
		return (report_error(cmd->argv[0], dest, errno));
	return (g_status.exit = OK);
}
