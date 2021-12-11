/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:35:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 15:05:11 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	builtin_unset(t_shell *mini)
{
	char	**argv;

	if (mini && mini->command && mini->command->value.simple.argv)
		argv = mini->command->value.simple.argv;
	if (argv[0] != NULL && argv[1] == NULL)
		return (0);
	while (*++argv)
	{
		//if (legal_identifier(key) == 0)
		//	return (1);
		if (declare_remove(&mini->env.declare, *argv) != 0)
			return (1);
	}
	if (!replace_envp(&mini->env, 1))
		return (1);
	return (0);
}
