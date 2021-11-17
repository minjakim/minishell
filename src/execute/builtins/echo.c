/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:18:16 by snpark            #+#    #+#             */
/*   Updated: 2021/11/15 17:23:41 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	builtin_echo(char **argv, t_io stream, int *exit_status)
{
	int	display_return;
	int	i;

	if (argv == NULL)
		return (0);
	display_return = 1;
	i = 0;
	if (argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][2] == '\0' && ++i)
		display_return = 0;
	while (argv[++i] != NULL)
	{
		write(stream.out, argv[i], strlen(argv[i]));
		if (argv[i + 1] != NULL)
			write(stream.out, " ", 1);
	}
	if (display_return)
		write(stream.out, "\n", 1);
	*exit_status = 0;
	return (1);
}
