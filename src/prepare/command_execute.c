/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/17 16:30:56 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char
	**make_argv(t_word_list *list, int argc)
{
	char	**dest;
	int		i;

	dest = xmalloc(sizeof(char *) * (argc + 1));
	ft_memset(dest, 0, sizeof(char *) * (argc + 1));
	i = -1;
	while (list)
	{
		dest[++i] = ft_strdup(list->word.word);
		list = list->next;
	}
	dest[i + 1] = NULL;
	return (dest);
}

int
	command_execute(t_shell *mini)
{
	t_command		*command;
	pid_t			pid;
	t_io			pipe_fd;

	command = mini->command;
	while (command)
	{
		pid = 0;
		if (command->flags & CMD_PIPE)
			pid = command_pipe_set(mini);
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			expand_command(mini);
			command->argv = make_argv(command->words, command->argc);
			if (command->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
				command_redirect(mini);
			command_find(mini);
			mini->execute[is_builtin(command->argv[0])]((const t_command*)command);
			//if (expand_command() != 0)
			//	return (1);
			//if (command->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
			//	if (redirect() != 0)
			//		return (1);
			//if (find_command() != 0)
			//	return (127);
			//mini->err.exit_status = shell_execve[is_builtin()](mini);
			if (g_status.interactive == 0)
				exit(g_status.exit);
		}
		command_io_close(command->io);
		command_io_set(g_status.backup.stdio);
		command = command->next;
	}
	return (0);
}
