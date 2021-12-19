/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:07:43 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 18:55:41 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	heredoc(t_redirect *heredoc)
{
	char	*line;
	ssize_t	len;

	if (pipe(g_status.heredoc.fd) == ERROR)
		report_error("heredoc", "pipe", errno);
	remove_quote(heredoc->here_doc_eof);
	while (LOOP && !g_status.interrupted)
	{
		line = readline(SECOND);
		if (!g_status.interrupted)
		{
			if (!line || !ft_strcmp(line, heredoc->here_doc_eof))
				break ;
			if (!(heredoc->redirectee.filename.flags & (W_QUOTED | W_DQUOTED)))
				;
			len = ft_strlen(line);
			if (len != write(g_status.heredoc.out, line, len))
				report_error("heredoc", "write", errno);
			write(g_status.heredoc.out, "\n", 1);
			if (line)
				free(line);
		}
	}
	if (line)
		free(line);
	close(g_status.heredoc.out);
	return (g_status.heredoc.in);
}

int
	make_heredoc(const t_command *cmd)
{
	t_redirect	*redirects;

	while (cmd)
	{
		redirects = cmd->redirects;
		while (redirects)
		{
			if (redirects->here_doc_eof)
				redirects->redirectee.dest = heredoc(redirects);
			redirects = redirects->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
