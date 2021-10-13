/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 07:56:17 by snpark            #+#    #+#             */
/*   Updated: 2021/10/13 11:19:36 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	legal_variable_starter(char c)
{
	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	legal_identifier(char *name)
{
	int	i;

	if (!name || !*name || legal_variable_starter(*name) == 0)
		return (0);
	i = 0;
	while (name[++i] != '\0')
		if (legal_variable_starter(name[i]) == 0)
			return (0);
	return (1);
}

int	ms_unset(char **argv, char **envp)
{
	t_key_value_idx idx;
	int				last_i;

	if (argv == NULL || argv[1] == NULL)
		return (1);
	if (legal_identifier(argv[1]) == 0)
	{
		write(2, "bash: ", 6);
		write(2, "unset: `", 8);
		write(2, argv[1], strlen(argv[1]));
		write(2, "': is not a valid identifier\n", 29);
		exit(1);
	}
	last_i = -1;
	while (envp[++last_i] != NULL)
		;
	idx = ms_getenv(argv[1], envp);
	if (idx.key != -1)
	{
		free (envp[idx.key]);
		envp[idx.key] = envp[last_i];
		envp[last_i] = NULL;
	}
	return (1);
}

/*
**쉘 변수도 unset가능
**인자에 '='이 들어가면 에러
**bash: unset: 'argv[1]': is not a valid identifier
*/
