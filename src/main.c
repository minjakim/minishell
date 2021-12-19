/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 12:35:22 by minjakim         ###   ########.fr       */
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
	t_command	*command;

	line = NULL;
	while (LOOP)
	{
		if (!mini_readline(&line))
			continue ;
		words = parse_line(line);
		if (!words)
			continue ;
		command = parse_words(words);
		if (!make_heredoc(command))
			continue ;
		pj(command);
		execute_handler(command);
		dispose(command);
	}
	return (g_status.exit);
}

void
	pj(const t_command *command)
{
	while (command)
	{
		printf("flag: %d in: %d out: %d\n", command->flags & CMD_PIPE, command->io.in, command->io.out);
		command = command->next;
	}
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
