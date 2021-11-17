/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:32 by snpark            #+#    #+#             */
/*   Updated: 2021/11/14 20:44:26 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	ms_env(char **argv, char **envp, int stream_out, int *exit_status)
{
	if (argv[1] != NULL)
	{
		errno = ENOENT;
		cmd_arg_err("env", argv[1]); 
		*exit_status = 127;
		return (1);
	}
	while (*envp != NULL)
	{
		write(stream_out, *envp, strlen(*envp));
		write(stream_out, "\n", 1);
		++envp;
	}
	*exit_status = 0;
	return (1);
}
