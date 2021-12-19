/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:07:43 by snpark            #+#    #+#             */
/*   Updated: 2021/12/18 20:27:19 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	heredoc(t_redirect *heredoc)
{
	char	*line;

	pipe(g_status.heredoc.fd);
	remove_quote(heredoc->here_doc_eof);
	while (LOOP)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, heredoc->here_doc_eof))
			break ;
		if (!(heredoc->redirectee.filename.flags & (W_QUOTED | W_DQUOTED)))
			;//expand_str(line);
		write(g_status.heredoc.out, line, ft_strlen(line));
		write(g_status.heredoc.out, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(g_status.heredoc.out);
	return (g_status.heredoc.in);
}

int
	make_heredoc(t_command *command)
{
	t_redirect	*handler;

	while (command)
	{
		handler = command->redirects;
		while (handler)
		{
			if (handler->here_doc_eof)
				handler->redirectee.dest = heredoc(handler);
			handler = handler->next;
		}
		command = command->next;
	}
	return (SUCCESS);
}
