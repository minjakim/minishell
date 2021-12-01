/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:17:56 by snpark            #+#    #+#             */
/*   Updated: 2021/12/01 15:30:32 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	print_envp(char **envp)
{
	char **handle;

	handle = envp;
	while (*handle)
	{
		printf("%s\n", *handle);
		++handle;
	}
	return (0);	
}

int
	mini_env(t_shell *mini)
{
	return (print_envp(mini->env.envp));
}
