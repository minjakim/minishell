/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:24:37 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 12:30:21 by minjakim         ###   ########.fr       */
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

int
	execute_command_external(t_command *command)
{
	if (xfork() == 0)
	{
		expand_command(command);
		command->argv = make_argv(command->words, command->argc);
		if (command->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
			redirect_io(command);
		g_status.execute[find_command(command)]((const t_command*)command);
	}
	return (0);
}

int
	execute_command_internal(t_command *command)
{
	return (0);
}


int
	make_command(t_command *command)
{
	return (SUCCESS);
}

int
	execute_handler(t_command *command)
{
	while (command)
	{
		if ((command->flags & CMD_SUBSHELL) && xfork() == 0)
			if (command->flags & CMD_PIPE)
				set_io(&command->io);
		if (g_status.haschild == 0)
		{
			expand_command(command);
			command->argv = make_argv(command->words, command->argc);
			if (command->flags & (CMD_STDIN_REDIR | CMD_STDOUT_REDIR))
				redirect_io(command);
			g_status.execute[find_command(command)]((const t_command*)command);
		}
		if (g_status.haschild && !(command->flags & CMD_IGNORE_RETURN))
		{
			if (waitpid(g_status.haschild, &g_status.exit, 0) == ERROR)
				report_error(NULL, NULL, errno);
			if (g_status.exit && g_status.exit <= SIGUSR2)
				signal_report(g_status.exit);
			while (wait(NULL) != ERROR)
				;
		}
		reset_io(&command->io);
		command = command->next;
	}
	g_status.haschild = FALSE;
	return (SUCCESS);
}
