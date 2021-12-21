/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:07:43 by snpark            #+#    #+#             */
/*   Updated: 2021/12/21 10:03:08 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//remove_quote(heredoc->heredoc_eof);

static int
	write_heredoc(t_redirectee *heredoc)
{
	const char *const	eof = remove_quote(heredoc->filename.eof);
	char				*line;
	ssize_t				len;

	line = NULL;
	while (!g_status.state.any)
	{
		g_status.state.readline = TRUE;
		line = readline(SECOND);
		g_status.state.readline = FALSE;
		if (!line)
			handling_eof();
		if (!line || g_status.state.any || !ft_strcmp(line, eof))
			break ;
		if (!(heredoc->filename.flags & (W_QUOTED | W_DQUOTED)))
			line = expand_str(line, TRUE);
		len = ft_strlen(line);
		if (len != write(g_status.heredoc.out, line, len))
			g_status.state.error = report_error("heredoc", "write", errno);
		if (write(g_status.heredoc.out, "\n", 1) < 1)
			g_status.state.error = report_error("heredoc", "write", errno);
		free(line);
	}
	xfree(line);
	close(g_status.heredoc.out);
	return (g_status.heredoc.in);
}

int
	make_heredoc(const t_command *cmd)
{
	t_redirect	*rdx;

	while (!g_status.state.any && cmd)
	{
		rdx = cmd->redirects;
		while (!g_status.state.any && rdx)
		{
			if ((rdx->redirectee.filename.flags & W_HEREDOC) && \
							xpipe(g_status.heredoc.fd, "heredoc") != ERROR)
				rdx->redirectee.dest = write_heredoc(&rdx->redirectee);
			g_status.heredoc.value = 0;
			rdx = rdx->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
