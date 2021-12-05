/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:22:25 by snpark            #+#    #+#             */
/*   Updated: 2021/12/04 20:53:31 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	minishell(t_shell *mini)
{
	while (1)
	{
		mini->line = readline(PROMPT);
		if (mini->line == NULL)
			break ;
		add_history(mini->line);
		if (parse_line(mini) != 0)
			return (1);
		if (make_cmd(mini) != 0)
			return (1);
		if (execute_cmd(mini) != 0)
			return (1);
		free(mini->line);
	}
	if (mini->line == NULL)
		;//handling_eof();
	return (0);
}
