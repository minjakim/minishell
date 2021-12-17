/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/17 14:31:22 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_status	g_status;

static void
	handling_eof(void)
{
	write(STDOUT_FILENO, "\033[1A", 4);
	write(STDOUT_FILENO, "\033[14C", 5);
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
	else if (**line)
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
		if (!*line)
			continue ;
		words = word_list_handler(line);
		if (!words)
			continue ;
		command_handler(words, mini);
		command_heredoc(mini->command);
		command_execute(mini);
		command_clean(mini);
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
