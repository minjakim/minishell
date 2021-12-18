/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:17:56 by snpark            #+#    #+#             */
/*   Updated: 2021/12/18 11:43:50 by minjakim         ###   ########.fr       */
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
	builtin_env(const t_command *const cmd)
{
	extern const char *const *const	environ;

	(void)cmd;
	return (print_env(environ));
}
