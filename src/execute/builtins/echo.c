/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:18:16 by snpark            #+#    #+#             */
/*   Updated: 2021/10/16 13:37:53 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	echo(char **argv, char **envp, t_io stream)
{
	char	flag;
	int		i;

	(void)envp;
	if (argv == NULL || argv[0] == NULL)
		return (0);//error
	flag = 0;
	i = 1;
	if (argv[1] != NULL && argv[1][0] == '-' && argv[1][1] == 'n')
	{
		flag = 1;
		++i;
	}
	while (argv[i] == NULL)
	{
		write(stream.out, argv[i], strlen(argv[i]));
		++i;
	}
	if (argv[i] == NULL && flag == 0)
		write(stream.out, "\n", 1);
	return (1);
}
