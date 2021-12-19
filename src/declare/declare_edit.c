/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_edit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:20:26 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 19:01:38 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	declare_cat(char *value, t_declare *declare, int flag)
{
	char	*temp;

	temp = xcalloc(sizeof(char *) * (ft_strlen(declare->value) + ft_strlen(value) + 1));
	ft_strcat(ft_strcpy(temp, declare->value), value);
	free(declare->value);
	declare->value = temp;
	return (0);
}

static int
	declare_change(char *value, t_declare *declare)
{
	if (declare->value != NULL)
		free(declare->value);
	else
		declare->flag &= ~H_KEYONLY;
	declare->value = ft_strdup(value);
	if (declare->value == NULL)
		return (1);
	return (0);
}

int
	declare_edit(char *value, t_declare *declare, int flag)
{
	if (value && declare && declare->value && ft_strcmp(value, declare->value) == 0 \
			&& !(flag & H_CAT))
		return (0);
	if (value == NULL && declare && declare->value == NULL)
		return (0);
	if (flag & H_CAT)
		return (declare_cat(value, declare, flag));
	else
		return (declare_change(value, declare));
	return (0);
}
