/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/02 12:40:38 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	execute_cmd(t_shell *mini)
{
	t_command	*cmd;

	cmd = mini->cmd;
	while (cmd)
	{
		if (cmd->type == cm_connection && cmd->value.connection.connector == '|')
			;
		if (cmd->type == cm_connection)
			cmd = cmd->value.connection.next;
		else if (cmd->type == cm_simple)
			return (0);
	}
	return (0);
}
