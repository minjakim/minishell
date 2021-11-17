/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:38:13 by snpark            #+#    #+#             */
/*   Updated: 2021/11/14 21:18:16 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	is_str_num(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 0x20)
		++i;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	}
	return (1);
}

int
	ms_exit(char **argv, t_io pipe, int *exit_status)
{
	if (!(pipe.in == -1 && pipe.out == -1))
	{
		*exit_status = 0;
		return (1);
	}
	write(2, "exit\n", 5);
	if (argv != NULL && argv[0] != NULL && argv[1] != NULL && argv[2] != NULL)
	{
		*exit_status = 1;
		write(2, "bash: exit: too many arguments\n", 31);
	}
	if (argv != NULL && argv[1] != NULL && is_str_num(argv[1]) == 0)
	{
		write(2, "bash: exit: ", 12);
		write(2, argv[1], strlen(argv[1]));
		write(2, ": numeric argument required\n", 28); 
		*exit_status = 0xff;
	}
	if (argv != NULL && argv[0] != NULL && argv[1] != NULL)
		*exit_status = atoi(argv[1]);
	exit(*exit_status & 0xff);
	return (1);
}
