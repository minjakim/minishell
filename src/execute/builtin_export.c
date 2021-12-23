/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:45:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 20:56:00 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	print_declare(t_declare *node)
{
	while (node)
	{
		if (node->exported)
		{
			printf("declare -x %s", node->key.str);
			if (node->value.str)
				printf("=\"%s\"\n", node->value.str);
			else
				printf("\n");
			node = node->next;
		}
	}
	return (g_status.exit = OK);
}

void
	declare_export_new(const char *key, const char *after)
{
	char	*line;

	if (*after == '+')
		++after;
	line = xcalloc(ft_strlen(key) + ft_strlen(after) + 1);
	ft_strcat(ft_strcpy(line, key), after);
	declare_add(line);
	xfree(line);
	g_status.env.tail->exported = TRUE;
	if (g_status.env.tail->line != NULL)
		++g_status.env.envc;
}

int
	declare_export_update_value(t_declare *node, char *str)
{
	char	*value;

	if (*str == '=' && ++str)
	{
		if (!*str)
			return (SUCCESS);
		value = xcalloc(node->value.len + ft_strlen(str) + 1);
		ft_strcat(ft_strcpy(value, node->value.str), str);
	}
	else
		value = ft_strdup(str);
	xfree(node->value.str);
	node->value.str = value;
	node->value.len = ft_strlen(node->value.str);
	xfree(node->line);
	node->line = declare_new_line(&node->key, &node->value);
	return (SUCCESS);
}

static void
	declare_export(const char *str)
{
	t_declare	*node;
	char		*key;
	int			index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '=' || str[index] == '+')
			break ;
		++index;
	}
	key = ft_strndup(str, index);
	node = declare_search(key);
	if (node)
		declare_export_update_value(node, (char *)&str[index + 1]);
	else
		declare_export_new(key, (char *)&str[index]);
	g_status.env.edited = TRUE;
	xfree(key);
}

int
	builtin_export(const t_command *const cmd)
{
	char	**argv;
	int		exception;

	argv = cmd->argv;
	exception = OK;
	if (argv[1] == NULL)
		return (print_declare(g_status.env.head));
	while (*++argv)
	{
		if (!declare_legal_check(*argv))
			report_exception(cmd->argv[0], *argv, EX_DECLARE, GENERAL_ERROR);
		else
			declare_export(*argv);
	}
	declare_update_envp();
	if (exception)
		return (g_status.exit = GENERAL_ERROR);
	return (g_status.exit = OK);
}
