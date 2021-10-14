/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:36:56 by snpark            #+#    #+#             */
/*   Updated: 2021/10/06 20:27:28 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd(char **argv, char **envp, int stream_out)
{
	char	*path;

	(void)argv;
	(void)envp;
	path = getcwd(NULL, 0);
	write(stream_out, path, strlen(path));
	write(stream_out, "\n", 1);
	free(path);
	return (1);
}
