/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:45:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/13 09:36:43 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	print_export(t_declare *handle)
{
	while (handle && handle->flag & H_EXPORT)
	{
		printf("declare -x ");
		printf("%s", handle->key);
		if (!(handle->flag & H_KEYONLY))
			printf("=\"%s\"", handle->value);
		printf("\n");
		handle = handle->next;
	}
	return (0);
}

int
	builtin_export(t_shell *mini)
{
	char	**argv;

	if (mini && mini->command && mini->command->argv)
		argv = mini->command->argv;
	else
		return (0);
	if (argv[0] != NULL && argv[1] == NULL)
		return (print_export(mini->env.declare));
	while (*++argv)
	{
		//if (legal_identifier(key) == 0)
		//	return (1);
		if (declare_add(&mini->env.declare, *argv, H_EXPORT) != 0)
			return (1);
	}
	return (0);
}
