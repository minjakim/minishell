/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:45:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/24 22:41:00 by minjakim         ###   ########.fr       */
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
	declare_export_new(const char *key, const char *str)
{
	char	*line;

	if (((*str == '+') && (*str + 2 == '\0')) || (*str + 1 == '\0'))
		declare_add(key);
	else
	{
		if (*str == '+')
			++str;
		line = xcalloc(ft_strlen(key) + ft_strlen(str) + 1);
		ft_strcat(ft_strcpy(line, key), str);
		declare_add(line);
		xfree(line);
	}
	g_status.env.tail->exported = TRUE;
	if (g_status.env.tail->line != NULL)
		++g_status.env.envc;
}

int
	declare_export_update_value(t_declare *node, char *str)
{
	char	*value;

	if (*str == '+' && ++str)
	{
		if (*(++str) == '\0' && !node->line)
			return (SUCCESS);
		value = xcalloc(node->value.len + ft_strlen(str) + 1);
		ft_strcat(ft_strcpy(value, node->value.str), str);
	}
	else if (++str && *str)
		value = ft_strdup(str);
	else
		value = xcalloc(sizeof(char));
	xfree(node->value.str);
	node->value.str = value;
	node->value.len = ft_strlen(node->value.str);
	xfree(node->line);
	node->line = NULL;
	if (*node->value.str)
		node->line = declare_new_line(&node->key, &node->value);
	return (SUCCESS);
}

static int
	declare_export(const char *str, int index)
{
	t_declare	*node;
	char		*key;

	if (!index)
		key = (char *)str;
	else
		key = ft_strndup(str, index);
	node = declare_search(key);
	if (node && !index)
		return (node->exported = TRUE);
	else if (node && index)
		return (declare_export_update_value(node, (char *)&(str[index])));
	else if (index)
		declare_export_new(key, (char *)&(str[index]));
	else
		declare_add(key)->exported = TRUE;
	if (index)
		xfree(key);
	return (g_status.env.edited = TRUE);
}

int
	builtin_export(const t_command *const cmd)
{
	char	**argv;
	int		exception;
	int		index;

	argv = cmd->argv;
	exception = OK;
	if (argv[1] == NULL)
		return (print_declare(g_status.env.head));
	while (*++argv)
	{
		index = declare_legal_check(*argv);
		if (index == EXCEPTION && ++exception)
			report_exception(cmd->argv[0], *argv, EX_DECLARE, GENERAL_ERROR);
		else
			declare_export(*argv, index);
	}
	declare_update_envp();
	if (exception)
		return (g_status.exit = GENERAL_ERROR);
	return (g_status.exit = OK);
}
