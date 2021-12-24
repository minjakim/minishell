/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/24 12:12:17 by snpark           ###   ########.fr       */
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
		if (!g_status.state.any)
			make_heredoc(cmd);
		if (!g_status.state.any)
			execute_handler(cmd);
		dispose_command(cmd);
	}
	return (g_status.exit);
}

static int
	ft_minishell_with_flag(char *line)
{
	t_word_list	*words;
	t_command	*cmd;

	words = parse_line(line);
	if (!words)
		return (g_status.exit);
	cmd = parse_words(words);
	if (!g_status.state.any)
		make_heredoc(cmd);
	if (!g_status.state.any)
		execute_handler(cmd);
	dispose_command(cmd);
	return (mini_exit(g_status.exit));
}

int
	main(int argc, char **argv, char **envp)
{
	g_status.env.envp = envp;
	init_signal();
	init_declare();
	init_status();
	init_execute();
	if (argc >= 2 && !ft_strcmp(MINI_OPTION, argv[1]))
	{
		if (argc == 2)
			return (report_exception_fatal(argv[1], EX_MINI, ES_BADUSAGE));
		return (ft_minishell_with_flag(argv[2]));
	}
	return (ft_minishell());
}
