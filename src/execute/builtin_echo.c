/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:05:04 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 18:55:41 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	builtin_echo(const t_command *const cmd)
{
	const char *const *const	argv = (const char *const *const)cmd->argv;
	int							display_return;
	int							i;
	int							n;

	display_return = TRUE;
	i = 1;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		n = 2;
		while (argv[i][n] == 'n')
			++n;
		if (argv[i][n] == '\0')
		{
			display_return = FALSE;
			++i;
		}
		else
			break ;
	}
	while (argv[i] && write(STDOUT_FILENO, argv[i], ft_strlen(argv[i])))
		if (argv[++i])
			write(STDOUT_FILENO, " ", 1);
	if (display_return)
		write(STDOUT_FILENO, "\n", 1);
	return (g_status.exit = OK);
}
