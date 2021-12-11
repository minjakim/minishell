/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 08:10:09 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

t_shell	*mini;

static inline char
	*ft_readline(t_buffer *buffer)
{
	if (buffer->line)
		free(buffer->line);
	buffer->line = NULL;
	buffer->line = readline(PROMPT);
	if (!buffer->line)
		eof_handler(mini);
	else
		add_history(buffer->line);
	return (buffer->line);
}

int
	minishell(t_shell *mini)
{
	t_buffer	buffer;

	while (1)
	{
		if (!ft_readline(&buffer))
			break ;
		parse_line(&buffer);
		make_cmd(buffer.node, mini);
		execute_cmd(mini);
		clean_cmd(mini);
	}
	return (mini->status.exit);
}

int
	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	mini = malloc(sizeof(t_shell));
	if (mini)
	{
		mini->env.envp = envp;
		initialize(mini);
		return (minishell(mini));
	}
	return (0);
//	if (initialize(&mini) != 0)
//		return (1);
////	if (minishell(&mini) != 0)
////		return (1);
//	glob_expand(NULL);
//	return (0);
}
