/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:03:50 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 18:55:41 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_str
	*get_t_str(const char *const str)
{
	t_str	*ptr;

	ptr = xcalloc(sizeof(t_str*));
	ptr->str = ft_strdup(str);
	ptr->len = ft_strlen(str);
	return (ptr);
}

static void
	set_node(const char *const key, const char *const value)
{
	t_declare	*node;
	char		*line;

	node = declare_search(key);
	printf("%p\n", node);
	if (node)
	{
		xfree(node->value.str);
		node->value.str = ft_strdup(value);
		node->value.len = ft_strlen(node->value.str);
		xfree(node->line);
		node->line = declare_new_line(&node->key, &node->value);
		printf("%s\n", node->line);
	}
	else
	{
		printf("%s %s\n", key, value);
		line = declare_new_line(get_t_str(key), get_t_str(value));
		declare_add(line);
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
	set_node(PWD, path);
	set_node(OLDPWD, from);
	declare_update_envp();
	disposer(from, path, NULL, NULL);
	return (OK);
}

static const char
	*get_path(const char *const *const argv)
{
	char	*path;

	if (argv[1] == NULL)
	{
		path = getenv(HOME);
		if (!path)
			report_exception(argv[0], NULL, EX_CD_HOME, GENERAL_ERROR);
		return (path);
	}
	else if (argv[1][0] == '-' && argv[1][1] == '\0')
	{
		path = getenv(OLDPWD);
		if (!path)
			report_exception(argv[0], NULL, EX_CD_OLDPWD, GENERAL_ERROR);
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
