/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_eof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:35:43 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/11 11:29:09 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	get_cursor_position(void)
{
	char	buffer[255];
	int		row;
	int		i;

	write(STDOUT_FILENO, "\033[6n", 4);
	i = read(STDIN_FILENO, buffer, 255);
	buffer[i] = '\0';
	i = 1;
	row = 0;
	while (!((unsigned)buffer[i] - 48 < 10))
		++i;
	while (((unsigned)buffer[i] - 48) < 10)
		row = (row << 1) + (row << 3) + (buffer[i++] - 48);
	return (row);
}

static int
	putchar_tc(int tc)
{
	write(STDOUT_FILENO, &tc, 1);
	return (0);
}

void
	eof_handler(t_shell *mini)
{
	mini->config.current.c_lflag &= ~ICANON;
	mini->config.current.c_lflag &= ~ECHO;
	mini->config.current.c_cc[VMIN] = 1;
	mini->config.current.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->config.current);
	tputs(tgoto(tgetstr("cm", NULL), sizeof(PROMPT) - 1, \
	get_cursor_position() - 2), 1, putchar_tc);
	write(STDERR_FILENO, "exit\n", 5);
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->config.backup);
}
