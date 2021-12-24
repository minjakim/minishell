/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 23:20:58 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/20 21:40:53 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	handling_eof(void)
{
	if (g_status.heredoc.value)
	{
		write(STDOUT_FILENO, "\033[1A", 4);
		write(STDOUT_FILENO, "\033[2C", 4);
		g_status.state.prompt += 2;
	}
	else
	{
		write(STDOUT_FILENO, "\033[1A", 4);
		while (--g_status.state.prompt)
			write(STDOUT_FILENO, "\033[1C", 4);
		write(STDERR_FILENO, EXIT, sizeof(EXIT) - 1);
		mini_exit(g_status.exit);
	}
}

char
	mini_readline(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
	g_status.state.readline = TRUE;
	*line = readline(PROMPT);
	g_status.state.readline = FALSE;
	if (*line == NULL)
		handling_eof();
	if (**line)
		add_history(*line);
	g_status.state.prompt = sizeof(PROMPT);
	g_status.state.any = FALSE;
	return (**line);
}
