/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 13:05:53 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_status	g_status;

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
	g_status.state.any = 0;
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
		if (!g_status.state.any)
			execute_handler(cmd);
		dispose_cmd(cmd);
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
