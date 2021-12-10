/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/09 12:57:20 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

t_shell	*mini;

int
	main(int argc, char **argv, char **envp)
{

	(void)argc;
	(void)argv;
	mini = malloc(sizeof(t_shell));
	if (mini)
	{
		mini->env.envp = envp;
		initialize(mini);
		return (minishell(mini));
	}
	return (0);
//	if (initialize(&mini) != 0)
//		return (1);
////	if (minishell(&mini) != 0)
////		return (1);
//	glob_expand(NULL);
//	return (0);
}
