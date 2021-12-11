/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:17:56 by snpark            #+#    #+#             */
/*   Updated: 2021/12/04 15:54:49 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	print_envp(const char **envp)
{
	while (*envp)
		printf("%s\n", *envp++);
	return (0);
}

int
	builtin_env(t_shell *mini)
{
	return (print_envp((const char **)mini->env.envp));
}
