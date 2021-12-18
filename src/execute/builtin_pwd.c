/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 09:53:58 by snpark            #+#    #+#             */
/*   Updated: 2021/12/18 13:07:36 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	builtin_pwd(const t_command *const cmd)
{
	const char *const	cwd = getcwd(NULL, 0);

	(void)cmd;
	if (cwd == NULL)
		return (FAILURE);
	printf("%s\n", cwd);
	return (SUCCESS);
}
