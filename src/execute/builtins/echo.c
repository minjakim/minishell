/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:18:16 by snpark            #+#    #+#             */
/*   Updated: 2021/10/15 11:27:07 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	echo(char **argv, char **envp, int stream_in, int stream_out)
{
	char	flag;
	int		i;

	(void)envp;
	(void)stream_in;
	if (argv == NULL || argv[0] == NULL)
		return (0);//error
	flag = 0;
	i = 1;
	if (argv[1] != NULL && argv[1][0] == '-' && argv[1][1] == 'n')
	{
		flag = 1;
		++i;
	}
	while(argv[i] == NULL)
	{
		write(stream_out, argv[i], strlen(argv[i]));
		++i;
	}
	if (argv[i] == NULL && flag == 0)
		write(stream_out, "\n", 1);
	return (1);
}
