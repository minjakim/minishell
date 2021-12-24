/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:51:01 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/20 20:55:24 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char
	*declare_new_line(const t_str *const key, const t_str *const value)
{
	char *const	line = xcalloc(key->len + value->len + 2);

	ft_strcat(line, key->str);
	*(line + key->len) = '=';
	ft_strcat((line + key->len), value->str);
	return (line);
}

t_declare
	*declare_new(const char *const str)
{
	t_declare	*node;

	node = xcalloc(sizeof(t_declare));
	if (!ft_strchr(str, '='))
	{
		node->key.str = ft_strdup(str);
		node->key.len = ft_strlen(str);
	}
	else
	{
		node->key.len = ft_strchr(str, '=') - str;
		node->key.str = ft_strndup(str, node->key.len);
		node->value.str = ft_strdup(ft_strchr(str, '=') + 1);
		node->value.len = ft_strlen(node->value.str);
		node->line = ft_strdup(str);
	}
	return (node);
}

t_declare
	*declare_add(const char *const str)
{
	g_status.env.tail->next = declare_new(str);
	g_status.env.tail->next->prev = g_status.env.tail;
	g_status.env.tail = g_status.env.tail->next;
	return (g_status.env.tail);
}

t_declare
	*declare_search(const char *const str)
{
	t_declare	*node;

	node = g_status.env.head;
	while (node && ft_strcmp(str, node->key.str))
		node = node->next;
	return (node);
}

char
	*declare_get_value(const char *const str)

{
	t_declare	*node;

	node = declare_search(str);
	if (node)
		return (node->value.str);
	else
		return (NULL);
}
