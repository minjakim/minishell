/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/13 11:24:29 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*g_mini;

static int
	put_tc(int tc)
{
	write(STDOUT_FILENO, &tc, 1);
	return (0);
}

static void
	eof_handler(void)
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
}

static inline char
	*ft_readline(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
	*line = readline(PROMPT);

	if (!*line)
		eof_handler();
	else
		add_history(*line);
	return (*line);
}

int
	minishell(t_shell *mini)
{
	char		*line;
	t_word_list	*words;

	while (LOOP)
	{
		if (!ft_readline(&line))
			break ;
		words = word_list_make(line);
		if (!words)
			return (GENERAL_ERROR);
	}
	return (builtin_exit(mini));
}

int
	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_mini = malloc(sizeof(t_shell));
	if (!g_mini)
		return (GENERAL_ERROR);
	g_mini->env.envp = envp;
	if (!initialize(g_mini))
		return (GENERAL_ERROR);
	return (minishell(g_mini));
}
