/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:22:25 by snpark            #+#    #+#             */
/*   Updated: 2021/12/10 14:16:37 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

static inline char
	*ft_readline(t_buffer *buffer)
{
	buffer->line = readline(PROMPT);
	return (buffer->line);
}

int
	minishell(t_shell *mini)
{
	t_buffer	buffer;

	while (1)
	{
		if (!ft_readline(&buffer))
		{
			eof_handler(mini);
			break ;
		}
		add_history(buffer.line);
		parse_line(&buffer);
		make_cmd(buffer.node, mini);
		execute_cmd(mini);
	}
	return (mini->status.exit);
}
