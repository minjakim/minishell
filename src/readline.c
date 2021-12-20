/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 23:20:58 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/19 23:22:02 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static inline void
	handling_eof(void)
{
	write(STDOUT_FILENO, "\033[1A", 4);
	if (g_status.state.any)
		write(STDOUT_FILENO, "\033[16C", 5);
	else
		write(STDOUT_FILENO, "\033[14C", 5);
	write(STDERR_FILENO, EXIT, sizeof(EXIT) - 1);
	mini_exit(g_status.exit);
}

static inline char
	mini_readline(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
	*line = readline(PROMPT);
	if (*line == NULL)
		handling_eof();
	else if (**line)
		add_history(*line);
	g_status.state.any = 0;
	return (**line);
}
