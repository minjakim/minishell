/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:32 by snpark            #+#    #+#             */
/*   Updated: 2021/10/15 11:27:11 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	ms_env(char **argv, char **envp, int stream_out)
{
	if (argv[1] != NULL)
	{
		write(2, "env: ", 5);
		write(2, argv[1], strlen(argv[1]));
		write(2, ": No such file of directory\n", 28);
		exit(errno);
	}
	while (*envp != NULL)
	{
		write(stream_out, *envp, strlen(*envp));
		write(stream_out, "\n", 1);
		++envp;
	}
	return (1);
}
