/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:36:56 by snpark            #+#    #+#             */
/*   Updated: 2021/11/15 14:53:11 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	pwd(int stream_out, int *exit_status)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		write(2, "bash: ", 6);
		write(2, strerror(errno), strlen(strerror(errno)));
		*exit_status = 1;
	}
	write(stream_out, path, strlen(path));
	write(stream_out, "\n", 1);
	free(path);
	*exit_status = 0;	
	return (1);
}
