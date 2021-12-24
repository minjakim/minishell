/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 09:53:58 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 18:55:41 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	builtin_pwd(const t_command *const cmd)
{
	char *const	cwd = getcwd(NULL, 0);

	if (cwd == NULL)
		return (report_error(cmd->argv[0], NULL, errno));
	printf("%s\n", cwd);
	xfree(cwd);
	return (g_status.exit = OK);
}
