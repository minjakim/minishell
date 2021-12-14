/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 09:53:58 by snpark            #+#    #+#             */
/*   Updated: 2021/12/04 14:47:48 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	builtin_pwd(t_command *command)
{
	char	*cwd;

	(void)command;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (1);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
