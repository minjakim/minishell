/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/15 18:02:29 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_status	g_status;

static int
	put_tc(int tc)
{
	return (write(STDOUT_FILENO, &tc, 1));
}

static void
	handling_eof(void)
{
	t_termios	temp;
	char		buffer[255];
	int			row;
	int			i;

	temp.c_lflag &= ~ICANON;
	temp.c_lflag &= ~ECHO;
	temp.c_cc[VMIN] = 1;
	temp.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &temp);
	write(STDOUT_FILENO, "\033[6n", 4);
	i = read(STDIN_FILENO, buffer, 254);
	buffer[i] = '\0';
	i = 1;
	row = 0;
	while (!((unsigned)buffer[i] - '0' < 10))
		++i;
	while ((unsigned)buffer[i] - '0' < 10)
		row = (row << 1) + (row << 3) + (buffer[i++] - '0');
	tputs(tgoto(tgetstr("cm", NULL), LEN_PROMPT, row - 2), 1, put_tc);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_status.backup.attr);
	write(STDERR_FILENO, EXIT, LEN_EXIT);
}

static inline char
	*mini_readline(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
	*line = readline(PROMPT);
	if (!*line)
		handling_eof();
	else
		add_history(*line);
	return (*line);
}

static int
	ft_minishell(t_shell *mini)
{
	char		*line;
	t_word_list	*words;

	line = NULL;
	while (LOOP)
	{
		if (!mini_readline(&line))
			break ;
		words = word_list_handler(line);
		if (!words)
			return (mini_exit(GENERAL_ERROR));
	}
	return (mini_exit(g_status.exit));
}

int
	main(int argc, char **argv, char **envp)
{
	t_shell	mini;

	(void)argc;
	(void)argv;
	g_status.env.envp = envp;
	if (!initialize(&mini))
		return (GENERAL_ERROR);
	return (ft_minishell(&mini));
}