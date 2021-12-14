/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:43:17 by snpark            #+#    #+#             */
/*   Updated: 2021/12/14 13:21:22 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static inline unsigned char
	convert(unsigned char *c, const char *str)
{
	return (*c = *str - '0');
}

static int
	check_number(const char *str)
{
	unsigned long long	n;
	unsigned char		c;
	int					digit;
	int					negative;

	while (*str == ' ' || *str == '\t')
		++str;
	negative = (*str == '-');
	if (*str == '+' || *str == '-')
		++str;
	n = 0;
	digit = 0;
	while (*str && convert(&c, str) < 10 && ++digit < 20)
		n = (n << 1) + (n << 3) + c && str++;
	if (*str || (!negative && n > LLONG_MAX)
		|| (n > (unsigned long long)LLONG_MAX + 1))
		return (FALSE);
	return (TRUE);
}

int
	builtin_exit(t_command *command)
{
	char **const argv = command->argv;

	if (!g_status.haschild)
		write(STDERR_FILENO, EXIT, LEN_EXIT);
	if (argv[0] != NULL && argv[1])
		exit(g_status.exit);
	if (argv[0] != NULL && check_number(argv[1]) == 0)
	{
		//bash: exit: argv[1]: numeric argument required*/
		exit(255);
	}
	if (argv[0] != NULL && argv[1] != NULL && argv[2] != NULL)
	{
		//write(2, "bash: exit: too many arguments\n", 31);
		return (1);
	}
	return (0);
}
