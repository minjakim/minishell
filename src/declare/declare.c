/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:44:39 by snpark            #+#    #+#             */
/*   Updated: 2021/12/01 18:26:22 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	
	make_declare_head(t_hash **head, t_hash *back, t_hash tmp)
{
	t_hash *new;

	new = malloc(sizeof(t_hash));
	if (new == NULL)
		return (1);
	memset(new, 0, sizeof(t_hash));
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

int
	make_declare(t_hash *back, t_hash tmp)
{
	t_hash *new;

	new = malloc(sizeof(t_hash));
	if (new == NULL)
		return (1);
	memset(new, 0, sizeof(t_hash));
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

int
	add_declare_unit(t_hash **head, t_hash *back, t_hash tmp)
{
	if (back && back->next && strcmp(tmp.key, back->next->key) == 0\
			&& tmp.value == NULL)
		return (0);
	else if (back && back->next && strcmp(tmp.key, back->next->key) == 0)
		return (edit_declare_value(tmp.value, back->next, tmp.flag));
	else if (back == NULL || (back && strcmp(tmp.key, back->key) < 0))
		return (make_declare_head(head, back, tmp));
	else
		return (make_declare(back, tmp));
	return (1);
}

int 
	add_declare(t_hash **head, char *str, int flag)
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
	return (add_declare_unit(head, check_declare_key(*head, tmp.key), tmp));
}
