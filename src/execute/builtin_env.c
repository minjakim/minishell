/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:17:56 by snpark            #+#    #+#             */
/*   Updated: 2021/12/14 15:42:37 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	print_env(const char *const *const envp)
{
	register int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	return (SUCCESS);
}

int
	builtin_env(const t_command *const command)
{
	extern const char *const *const	environ;

	(void)command;
	return (print_env(environ));
}