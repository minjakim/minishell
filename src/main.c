/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 21:30:20 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_status	g_status;

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
	environ = envp;
	if (!initialize())
		return (GENERAL_ERROR);
	return (ft_minishell());
}
