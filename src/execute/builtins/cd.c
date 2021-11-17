/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:03:49 by snpark            #+#    #+#             */
/*   Updated: 2021/11/15 17:23:16 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	cd(char **argv, char **envp, int *exit_status)
{
	const char	*path = argv[1];
	int			ret;
	char		*tmp;

	if (path == NULL)
		ret = chdir(envp[ms_getenv("HOME", envp).key]);
	else
		ret = chdir(path);
	if (ret == -1)
	{
		bash_cmd_arg_err("cd", argv[1]);
		*exit_status = 1;
	}
	else
		*exit_status = 0;
	return (1);
}
