/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:35:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/12 15:14:37 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	builtin_unset(t_shell *mini)
{
	char	**argv;

	if (mini && mini->command && mini->command->argv)
		argv = mini->command->argv;
	if (argv[0] != NULL && argv[1] == NULL)
		return (0);
	while (*++argv)
	{
		//if (legal_identifier(key) == 0)
		//	return (1);
		if (declare_remove(&mini->env.declare, *argv) != 0)
			return (1);
	}
	return (0);
}
