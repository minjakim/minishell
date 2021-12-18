/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/18 17:44:07 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char
	**make_argv(t_word_list *list, int argc)
{
	char	**dest;
	int		i;

	dest = xcalloc(sizeof(char *) * (argc + 1));
	i = -1;
	while (list)
	{
		dest[++i] = ft_strdup(list->word.word);
		list = list->next;
	}
	dest[i + 1] = NULL;
	return (dest);
}

void
	cmd_io_close(t_io io)
{
	if (io.in != STDIN_FILENO)
		close(io.in);
	if (io.out != STDOUT_FILENO)
		close(io.out);
}

int
	cmd_io_set(t_io io)
{
	if (dup2(io.in, STDIN_FILENO) == ERROR)
		return (FAILURE);
	if (dup2(io.out, STDOUT_FILENO) == ERROR)
		return (FAILURE);
	return (SUCCESS);
}

int
	execute_cmd(t_command *cmd)
{
	expand_cmd(cmd);
	cmd->argv = make_argv(cmd->words, cmd->argc);
	if (cmd->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
		redirect(cmd);
	g_status.execute[find_cmd(cmd)]((const t_command*)cmd);
	if (!g_status.interactive)
		exit(g_status.exit);
	return (0);
}

int
	execute_handler(t_command *cmd)
{
	pid_t	pid;

	while (cmd)
	{
		pid = 0;
		if (cmd->flags & CMD_PIPE)
		{
			cmd_io_set(cmd->io);
			pid = fork();
		}
		if (pid == 0)
		{
			execute_cmd(cmd);
		}
		else if (pid > 0 && !(cmd->flags & CMD_IGNORE_RETURN))
		{
			waitpid(pid, &g_status.exit, 0);
			while (wait(NULL) != -1)
				;
		}
		cmd_io_close(cmd->io);
		cmd_io_set(g_status.backup.stdio);
		cmd = cmd->next;
	}
	return (SUCCESS);
}
