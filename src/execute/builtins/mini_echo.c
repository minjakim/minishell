/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:05:04 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 07:43:18 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	mini_echo(t_shell *mini)
{
	int		display_return;
	int		i;
	char	**argv;

	display_return = 1;
	i = 1;
	if (mini && mini->cmd)
		argv = mini->cmd->value.simple.argv;
	else
		return (0);
	if (argv[0] != NULL && strcmp(argv[1], "-n") == 0 && ++i)
	{
		display_return = 0;
		++i;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[++i])
			printf(" ");
	}
	if (display_return)
		printf("\n");
	return (0);
}
