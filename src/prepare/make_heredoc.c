/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:07:43 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 00:02:43 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//remove_quote(heredoc->here_doc_eof);

static int
	heredoc(t_redirect *heredoc)
{
	char	*line;
	ssize_t	len;

	if (pipe(g_status.heredoc.fd) == ERROR)
		report_error("heredoc", "pipe", errno);
	while (!g_status.state.any)
	{
		g_status.state.readline = TRUE;
		line = readline(SECOND);
		g_status.state.readline = FALSE;
		if (!line)
			handling_eof();
		if (g_status.state.any || !line || \
			 !ft_strcmp(line, heredoc->here_doc_eof))
			break ;
		if (!(heredoc->redirectee.filename.flags & (W_QUOTED | W_DQUOTED)))
			;
		len = ft_strlen(line);
		if (len != write(g_status.heredoc.out, line, len))
			g_status.state.error = report_error("heredoc", "write", errno);
		if (write(g_status.heredoc.out, "\n", 1) < 1)
			g_status.state.error = report_error("heredoc", "write", errno);
		free(line);
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

	while (!g_status.state.any && cmd)
	{
		redirects = cmd->redirects;
		while (!g_status.state.any && redirects)
		{
			if (redirects->here_doc_eof)
				redirects->redirectee.dest = heredoc(redirects);
			g_status.heredoc.value = 0;
			redirects = redirects->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
