/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:35:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/18 11:43:50 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	builtin_unset(const t_command *const cmd)
{
	char	**argv;

	argv = cmd->argv;
	//if (argv[0] != NULL && argv[1] == NULL)
	//	return (0);
	//while (*++argv)
	//{
	//	//if (legal_identifier(key) == 0)
	//	//	return (1);
	//	if (declare_remove(&mini->env.declare, *argv) != 0)
	//		return (1);
	//}
	return (0);
}
