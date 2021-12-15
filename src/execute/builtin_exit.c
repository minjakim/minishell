/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:43:17 by snpark            #+#    #+#             */
/*   Updated: 2021/12/15 15:03:43 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static inline unsigned char
	convert(unsigned char *const c, const char *const str)
{
	return (*c = *str - '0');
}

static int
	legal_number(const char *str)
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
	g_status.exit = (unsigned char)n;
	return (TRUE);
}

int
	mini_exit(const int exit_status)
{
	g_status.exit = exit_status;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_status.backup.attr) == ERROR)
		g_status.exit = ERR_NO_GENERAL;
	exit(g_status.exit);
}

int
	builtin_exit(const t_command *const command)
{
	const char *const *const	argv = (const char *const *const)command->argv;

	if (g_status.interactive)
		write(STDERR_FILENO, EXIT, LEN_EXIT);
	if (argv[1] == NULL)
		return (mini_exit(g_status.exit));
	if (!legal_number(argv[1]))
		return (mini_exit(exception_report(argv[0], argv[1], \
			ERR_MSG_EXIT_FMT, ERR_NO_EXIT_FMT)));
	else if (argv[2] != NULL)
		return (mini_exit(exception_report(argv[0], NULL, \
			ERR_MSG_EXIT_ARGS, ERR_NO_GENERAL)));
	else
		return (mini_exit(g_status.exit));
}
