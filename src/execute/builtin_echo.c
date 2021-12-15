/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:05:04 by snpark            #+#    #+#             */
/*   Updated: 2021/12/15 17:44:18 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	builtin_echo(const t_command *const command)
{
	const char *const *const	argv = (const char *const *const)command->argv;
	int							display_return;
	int							i;

	display_return = 1;
	i = 1;
	if (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n' && argv[i][2] == '\0')
	{
		display_return = 0;
		++i;
	}
	while (argv[i] && write(STDOUT_FILENO, argv[i], ft_strlen(argv[i])))
		if (argv[++i])
			write(STDOUT_FILENO, " ", 1);
	if (display_return)
			write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
