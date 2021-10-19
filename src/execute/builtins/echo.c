/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:18:16 by snpark            #+#    #+#             */
/*   Updated: 2021/10/19 11:49:59 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	builtin_echo(char **argv, char **envp, t_io stream)
{
	int	display_return;
	int	i;

	(void)envp;
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
	return (1);
}
