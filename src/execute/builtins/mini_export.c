/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:45:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/01 16:17:02 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	print_export(t_hash *handle)
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
	mini_export(t_shell *mini)
{
	/*no args*/
	return (print_export(mini->env.declare));
	/*args*/
//	if (add_declare(&mini->env.declare, mini->args[1], H_EXPORT) != 0)
//		return (1);
//	if (replace_envp(&mini->env, 1) != 0)
//		return (1);
}
