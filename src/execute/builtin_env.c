/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:17:56 by snpark            #+#    #+#             */
/*   Updated: 2021/12/14 13:44:58 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	print_envp(const char **envp)
{
	while (*envp)
		printf("%s\n", *envp++);
	return (SUCCESS);
}

int
	builtin_env(t_command *command)
{
	extern char **environ;

	(void)command;
	return (print_envp((const char **)environ));
}
