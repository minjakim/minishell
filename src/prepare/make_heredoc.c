/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:07:43 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 12:23:06 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//remove_quote(heredoc->heredoc_eof);

static int
	write_heredoc(t_redirect *heredoc)
{
	const char *const	eof = heredoc->heredoc_eof;
	char				*line;
	ssize_t				len;

	while (!g_status.state.any)
	{
		if (!mini_readline(&line) || g_status.state.any || !ft_strcmp(line, eof))
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
	xfree(line);
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
			if (redirects->heredoc_eof && \
							xpipe(g_status.heredoc.fd,"heredoc") != ERROR)
				redirects->redirectee.dest = write_heredoc(redirects);
			g_status.heredoc.value = 0;
			redirects = redirects->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
