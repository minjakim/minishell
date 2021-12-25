/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:45:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/25 20:33:05 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	print_declare(t_declare *node)
{
	while (node)
	{
		printf("declare -x %s", node->key.str);
		if (node->value.str)
			printf("=\"%s\"\n", node->value.str);
		else
			printf("\n");
		node = node->next;
	}
	return (g_status.exit = OK);
}

void
	declare_export_new(const char *key, const char *str, t_export type)
{
	char	*line;

	if (type == C_ONLY || type == CAT)
		++str;
	line = xcalloc(ft_strlen(key) + ft_strlen(str) + 1);
	ft_strcat(ft_strcpy(line, key), str);
	declare_add(line);
	xfree(line);
	if (g_status.env.tail->type != K_ONLY)
		++g_status.env.envc;
}

int
	declare_export_update_value(t_declare *node, char *str, t_export type)
{
	char	*value;

	value = NULL;
	if (type == EXPORT || type == E_ONLY || \
							(type == C_ONLY && node->type == K_ONLY))
		value = ft_strdup(str);
	else if ((type == CAT || type == C_ONLY) && node->type != K_ONLY)
	{
		value = xcalloc(node->value.len + ft_strlen(str) + 1);
		ft_strcat(ft_strcpy(value, node->value.str), str);
	}
	if (node->type != K_ONLY)
		disposer(node->value.str, node->line, NULL, NULL);
	node->value.str = value;
	node->value.len = ft_strlen(node->value.str);
	node->line = declare_new_line(&node->key, &node->value);
	node->type = EXPORT;
	value = NULL;
	return (SUCCESS);
}

static int
	declare_export(const char *str, int i, t_export type)
{
	char *const	key = ft_strndup(str, i);
	t_declare	*node;

	node = declare_search(key);
	if (node && node->type == EXPORT && (type & (K_ONLY | C_ONLY)))
	{
		xfree(key);
		return (OK);
	}
	if (node && type == EXPORT)
		declare_export_update_value(node, (char *)&(str[i + 1]), type);
	else if (node && type == CAT)
		declare_export_update_value(node, (char *)&(str[i + 2]), type);
	else if (node && (type == E_ONLY || \
								((node->type & K_ONLY) && (type & C_ONLY))))
		declare_export_update_value(node, "", type);
	else if (!node && type != K_ONLY)
		declare_export_new(key, (char *)&(str[i]), type);
	else if (!node && (type == K_ONLY))
		declare_add(key);
	xfree(key);
	return (g_status.env.edited = TRUE);
}

int
	builtin_export(const t_command *const cmd)
{
	t_dc	dc;
	char	**argv;
	int		exception;

	argv = cmd->argv;
	exception = OK;
	if (argv[1] == NULL)
		return (print_declare(g_status.env.head));
	while (*++argv)
	{
		dc = declare_legal_check(*argv);
		if (dc.type == EXCEPTION && ++exception)
			report_exception(cmd->argv[0], *argv, EX_DECLARE, GENERAL_ERROR);
		else
			declare_export(*argv, dc.i, dc.type);
	}
	declare_update_envp();
	if (exception)
		return (g_status.exit = GENERAL_ERROR);
	return (g_status.exit = OK);
}
