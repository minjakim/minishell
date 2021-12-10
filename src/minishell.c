/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:22:25 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 07:39:40 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static inline char
	*ft_readline(t_buffer *buffer)
{
	if (buffer->line)
		free(buffer->line);
	buffer->line = NULL;
	buffer->node = NULL;
	buffer->line = readline(PROMPT);
	return (buffer->line);
}

void
	clean_cmd(t_shell *mini)
{
	t_word_list *wl_handler;
	t_redirect	*rd_handler;
	void		*tmp;
	int			i;

	while (mini->cmd)
	{
		wl_handler = mini->cmd->value.simple.words;
		while (wl_handler)
		{
			tmp = wl_handler->next;
			free(wl_handler);
			wl_handler = tmp;
		}
		i = -1;
		if (mini->cmd->value.simple.argv)
		{
			while (mini->cmd->value.simple.argv[++i])
				free(mini->cmd->value.simple.argv[i]);
			free(mini->cmd->value.simple.argv);
		}
		rd_handler = mini->cmd->value.simple.redirects;
		while (rd_handler)
		{
			if (rd_handler->flags == 0)
				free(rd_handler->here_doc_eof);
			else
				free(rd_handler->redirectee.filename.word);
			tmp = rd_handler->next;
			free(rd_handler);
			rd_handler = tmp;
		}
		if (mini->cmd->value.simple.path)
			free(mini->cmd->value.simple.path);
		if (mini->cmd->type == cm_connection)
		{
			tmp = mini->cmd->value.connection.next;
			free(mini->cmd);
			mini->cmd = tmp;
		}
		if (mini->cmd->type == cm_simple)
		{
			free(mini->cmd);
			mini->cmd = NULL;
		}
	}
}

int
	minishell(t_shell *mini)
{
	t_buffer	buffer;

	while (1)
	{
		if (!ft_readline(&buffer))
		{
			eof_handler(mini);
			break ;
		}
		add_history(buffer.line);
		parse_line(&buffer);
		make_cmd(buffer.node, mini);
		execute_cmd(mini);
		clean_cmd(mini);
	}
	return (mini->status.exit);
}
