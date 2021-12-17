/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/17 18:59:46 by minjakim         ###   ########.fr       */
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
	*mini_readline()
{
	if (g_status.line)
		free(g_status.line);
	g_status.line = NULL;
	g_status.line = readline(PROMPT);
	if (!g_status.line)
		handling_eof();
	else if (*g_status.line)
		add_history(g_status.line);
	return (g_status.line);
}

static int
	ft_minishell()
{
	t_word_list	*words;
	t_command	*command;

	while (LOOP)
	{
		if (!mini_readline())
			break ;
		if (!*g_status.line)
			continue ;
		words = word_list_handler(g_status.line);
		if (!words)
			continue ;
		command = command_handler(words);
		command_heredoc(command);
		command_execute(command);
		command_clean(command);
	}
	return (mini_exit(g_status.exit));
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
