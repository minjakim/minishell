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

static void
	set_node(const t_str *const key, const char *const str)
{
	t_declare	*node;
	t_str		value;

	node = declare_search(key->str);
	if (node)
	{
		xfree(node->value.str);
		node->value.str = ft_strdup(str);
		node->value.len = ft_strlen(node->value.str);
		xfree(node->line);
		node->line = declare_new_line(&node->key, &node->value);
		g_status.env.edited = TRUE;
	}
	else
	{
		value.str = (char *)str;
		value.len = ft_strlen(node->value.str);
		declare_add(declare_new_line(key, &value));
	}
}

static void
	set_path(const char *const cwd, const char *const path)
{
	const t_str	pwd_key = {.str = PWD, .len = sizeof(PWD) - 1};
	const t_str	old_key = {.str = OLDPWD, .len = sizeof(OLDPWD) - 1};

	set_node(&pwd_key, path);
	set_node(&old_key, cwd);
	declare_update_envp();
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
	const char *const	path = \
		get_path((const char *const *const)cmd->argv);
	const char *const	cwd = getcwd(NULL, 0);

	if (cwd == NULL)
		return (report_error(cmd->argv[0], NULL, errno));
	if (path == NULL)
		return (g_status.exit = GENERAL_ERROR);
	printf("%s %s\n", cwd, path);
	if (chdir(path) == ERROR)
		return (report_error(cmd->argv[0], path, errno));
	set_path(cwd, path);
	return (g_status.exit = OK);
}
