/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_declare_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:20:26 by snpark            #+#    #+#             */
/*   Updated: 2021/12/03 11:07:53 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	cat_declare_value(char *value, t_hash *hash, int flag)
{
	char *tmp;

	tmp = malloc(sizeof(char *) * (strlen(hash->value) + strlen(value) + 1));
	if (tmp == NULL)
		return (1);
	*tmp = '\0';
	strcat(strcpy(tmp, hash->value), value);
	free(hash->value);
	hash->value = tmp;
	return (0);
}

static int
	change_declare_value(char *value, t_hash *hash)
{
	if (hash->value != NULL)
		free(hash->value);
	else
		hash->flag &= ~H_KEYONLY;
	hash->value = strdup(value);
	if (hash->value == NULL)
		return (1);
	return (0);
}

int
	edit_declare_value(char *value, t_hash *hash, int flag)
{
	if (value && hash && hash->value && strcmp(value, hash->value) == 0\
			&& !(flag & H_CAT))
		return (0);
	if (value == NULL && hash && hash->value == NULL)
		return (0);
	if (flag & H_CAT) 
		return (cat_declare_value(value, hash, flag)); 
	else
		return (change_declare_value(value, hash));
	return (0);
}

