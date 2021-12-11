/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 19:06:52 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*mini;

static inline char
	*ft_readline(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
	*line = readline(PROMPT);
	if (!*line)
		handler_eof(mini);
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
		words = parse_line(line);
		if (!words)
			return (GENERAL_ERRORS);
		command_make(words, mini);
		command_execute(mini);
		//clean_command(mini);
	}
	return (mini->status.exit);
}

int
	initialize(char **envp)
{
	mini = malloc(sizeof(t_shell));
	if (!mini)
		return (FAIL);
	mini->env.envp = envp;
	if (!init_minishell(mini))
		return (FAIL);
	return (SUCCESS);
}

int
	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	if (!initialize(envp))
		return (GENERAL_ERRORS);
	return (minishell(mini));
}
