/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/18 17:45:07 by minjakim         ###   ########.fr       */
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
		cmd = make_cmd(words);
		if (!make_heredoc(cmd))
			continue ;
		execute_handler(cmd);
		dispose(cmd);
	}
	return (g_status.exit);
}

int
	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_status.env.envp = envp;
	if (!initialize())
		return (GENERAL_ERROR);
	return (ft_minishell());
}
