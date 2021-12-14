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
	builtin_pwd(const t_command *const command)
{
	const char *const	cwd = getcwd(NULL, 0);

	(void)command;
	if (cwd == NULL)
		return (FAILURE);
	printf("%s\n", cwd);
	return (SUCCESS);
}
