/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:43:17 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 14:38:41 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static inline unsigned char
	convert(unsigned char *c, const char *str)
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
	return (TRUE);
}

/*in bash
 * check internal and internal_shell variable
 * and if it's not internal(false)
 * don't print exit\n and exit*/

int
	builtin_exit(t_shell *mini)
{
	char	**argv;

	if (mini->status.interactive)
		write(STDERR_FILENO, "exit\n", 5);
	if (mini && mini->command && mini->command->value.simple.argv)
		argv = mini->command->value.simple.argv;
	if (argv[0] != NULL && argv[1])
		exit(mini->status.exit);
	if (argv[0] != NULL && legal_number(argv[1]) == 0)
	{
		//bash: exit: argv[1]: numeric argument required*/
		exit(255);
	}
	if (argv[0] != NULL && argv[1] != NULL && argv[2] != NULL)
	{
		//write(2, "bash: exit: too many arguments\n", 31);
		return (1);
	}
	//if (argv[0] != NULL && argv[1] != NULL)
		//exit(builtin_strtoll(argv[1]) & 0xff);
	return (0);
}
