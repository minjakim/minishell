/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_edit_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:20:26 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 13:56:04 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	cat_declare_value(char *value, t_hash *hash, int flag)
{
	char	*tmp;

	tmp = malloc(sizeof(char *) * (ft_strlen(hash->value) + ft_strlen(value) + 1));
	if (tmp == NULL)
		return (1);
	*tmp = '\0';
	ft_strcat(ft_strcpy(tmp, hash->value), value);
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
	hash->value = ft_strdup(value);
	if (hash->value == NULL)
		return (1);
	return (0);
}

int
	declare_edit_value(char *value, t_hash *hash, int flag)
{
	if (value && hash && hash->value && ft_strcmp(value, hash->value) == 0 \
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
