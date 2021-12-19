/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 19:36:48 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_status	g_status;

static inline void
	handling_eof(void)
{
	write(STDOUT_FILENO, "\033[1A", 4);
	write(STDOUT_FILENO, "\033[14C", 5);
	write(STDERR_FILENO, EXIT, sizeof(EXIT) - 1);
	mini_exit(g_status.exit);
}

static inline char
	mini_readline(char **line)
{
	if (*line)
		free(*line);
	g_status.interrupted = FALSE;
	*line = NULL;
	*line = readline(PROMPT);
	if (*line == NULL)
		handling_eof();
	else if (**line)
		add_history(*line);
	return (**line);
}

static int
	ft_minishell(void)
{
	char		*line;
	t_word_list	*words;
	t_command	*cmd;

	line = NULL;
	while (LOOP)
	{
		if (!mini_readline(&line))
			continue ;
		words = parse_line(line);
		if (!words)
			continue ;
		cmd = parse_words(words);
		make_heredoc(cmd);
		if (g_status.interrupted == FALSE)
			execute_handler(cmd);
		dispose(cmd);
	}
	return (g_status.exit);
}

int
	main(int argc, char **argv, char **envp)
{
	extern char **environ;

	(void)argc;
	(void)argv;
	g_status.env.envp = envp;
	environ = envp;
	if (!initialize())
		return (GENERAL_ERROR);
	return (ft_minishell());
}
