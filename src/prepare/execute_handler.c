/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/25 13:21:28 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	need_break(const t_command *const cmd)
{
	const int	connector = cmd->connector;

	if ((connector == W_NOFLAG) || (connector & W_PIPE))
		return (FALSE);
	if ((connector & W_AND_AND) && (g_status.exit == OK))
		return (FALSE);
	if ((connector & W_OR_OR) && (g_status.exit != OK))
		return (FALSE);
	return (TRUE);
}

static void
	afert_execute(const t_command *const cmd)
{
	t_declare	*node;

	node = declare_search(EXECUTED);
	if (node && cmd->argc == 0)
		declare_export_update_value(node, "", E_ONLY);
	else if (node)
		declare_export_update_value(node, cmd->argv[cmd->argc - 1], EXPORT);
	else if (cmd->argc == 0)
		declare_export_new(EXECUTED_KEY, "", E_ONLY);
	else
		declare_export_new(EXECUTED_KEY, cmd->argv[cmd->argc - 1], EXPORT);
	declare_update_envp();
}

static int
	pre_execute(t_command *const cmd)
{
	if (!expand_command(cmd))
		return (FAILURE);
	if (cmd->argc == 0)
		declare_update_node(EXECUTED, "");
	else
		declare_update_node(EXECUTED, cmd->argv[cmd->argc - 1]);
	declare_update_envp();
	if (cmd->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
		return (redirect_io(cmd));
	set_io(&cmd->io);
	return (SUCCESS);
}

int
	execute_handler(t_command *cmd)
{
	while (cmd)
	{
		if ((cmd->flags & CMD_PIPE) && xfork() == 0)
			cmd->flags |= CMD_SUBSHELL;
		if (g_status.state.haschild == 0)
		{
			if (pre_execute(cmd))
				g_status.execute[find_command(cmd)]((const t_command*)cmd);
			if (cmd->flags & CMD_SUBSHELL)
				exit(g_status.exit);
			afert_execute(cmd);
		}
		if (g_status.state.haschild && !(cmd->flags & CMD_IGNORE_RETURN))
			xwait(g_status.state.haschild, &cmd->io);
		else
			reset_io(&cmd->io);
		g_status.state.haschild = FALSE;
		if (need_break(cmd))
			break ;
		cmd = cmd->next;
	}
	g_status.interactive = TRUE;
	return (SUCCESS);
}
