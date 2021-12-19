/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:43:17 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 18:55:41 by minjakim         ###   ########.fr       */
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
		g_status.exit = GENERAL_ERROR;
	exit(g_status.exit);
}

int
	builtin_exit(const t_command *const cmd)
{
	const char *const *const	argv = (const char *const *const)cmd->argv;

	if (g_status.interactive)
		write(STDERR_FILENO, EXIT, LEN_EXIT);
	if (argv[1] == NULL)
		return (mini_exit(g_status.exit));
	if (!legal_number(argv[1]))
		report_exception(argv[0], argv[1], EX_EXIT_FMT, ES_EXIT_FMT);
	else if (argv[2] != NULL)
		return (report_exception(argv[0], NULL, EX_EXIT_ARGS, GENERAL_ERROR));
	return (mini_exit(g_status.exit));
}
