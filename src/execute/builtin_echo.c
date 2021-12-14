/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:05:04 by snpark            #+#    #+#             */
/*   Updated: 2021/12/14 13:43:41 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	builtin_echo(t_command *command)
{
	char	**argv;
	int		display_return;

	argv = ++command->argv;
	display_return = 1;
	if (*argv && *argv[0] == '-' && *argv[1] == 'n' && *argv[2] == '\0')
	{
		display_return = 0;
		++argv;
	}
	while (*argv && printf("%s", *argv))
		if (++argv)
			printf(" ");
	if (display_return)
		printf("\n");
	return (SUCCESS);
}
