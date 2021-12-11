/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:44:39 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 10:59:52 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_hash
	*declare_check_key(t_hash *head, const char *const key)
{
	t_hash	*back;
	t_hash	*handle;

	handle = head;
	back = handle;
	while (handle)
	{
		if (*key == *handle->key && strcmp(key, handle->key) == 0)
			return (back);
		if (strcmp(key, handle->key) < 0)
			return (back);
		back = handle;
		handle = handle->next;
	}
	return (back);
}

static int
	declare_make_head(t_hash **head, t_hash *back, t_hash tmp)
{
	t_hash	*new;

	new = malloc(sizeof(t_hash));
	if (new == NULL)
		return (1);
	ft_memset(new, 0, sizeof(t_hash));
	new->flag = tmp.flag;
	*head = new;
	new->next = back;
	new->key = strdup(tmp.key);
	if (new->key == NULL)
		return (1);
	if (new->flag & H_KEYONLY)
		new->value = NULL;
	else
	{
		new->value = strdup(tmp.value);
		if (new->value == NULL)
			return (1);
	}
	return (0);
}

static int
	declare_make(t_hash *back, t_hash tmp)
{
	t_hash	*new;

	new = malloc(sizeof(t_hash));
	if (new == NULL)
		return (1);
	ft_memset(new, 0, sizeof(t_hash));
	new->flag = tmp.flag;
	new->next = back->next;
	back->next = new;
	new->key = strdup(tmp.key);
	if (new->key == NULL)
		return (1);
	if (new->flag & H_KEYONLY)
		new->value = NULL;
	else
	{
		new->value = strdup(tmp.value);
		if (new->value == NULL)
			return (1);
	}
	return (0);
}

static int
	declare_add_unit(t_hash **head, t_hash *back, t_hash tmp)
{
	if (back && back->next && strcmp(tmp.key, back->next->key) == 0 \
			&& tmp.value == NULL)
		return (0);
	else if (back && back->next && strcmp(tmp.key, back->next->key) == 0)
		return (declare_edit_value(tmp.value, back->next, tmp.flag));
	else if (back == NULL || (back && strcmp(tmp.key, back->key) < 0))
		return (declare_make_head(head, back, tmp));
	else
		return (declare_make(back, tmp));
	return (1);
}

int
	declare_add(t_hash **head, char *str, int flag)
{
	int		offset;
	t_hash	tmp;

	offset = assignment(str);
	if (offset == 0 && legal_identifier(str) == 0)
		return (1);
	if (str[offset - 1] == '+')
	{
		str[offset - 1] = '\0';
		flag |= H_CAT;
	}
	if (offset != 0)
		str[offset] = '\0';
	tmp.key = str;
	tmp.value = str + offset + 1;
	if (offset == 0)
	{
		tmp.value = NULL;
		flag |= H_KEYONLY;
	}
	tmp.flag = flag;
	declare_check_key(*head, tmp.key);
	return (declare_add_unit(head, declare_check_key(*head, tmp.key), tmp));
}
