/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:40:25 by snpark            #+#    #+#             */
/*   Updated: 2021/10/06 21:12:54 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_env(char *key, char **envp)
{
	int	i;
	int	cmp_i;
	int	str_len;

	i = -1;
	str_len = strlen(key);
	while(envp[++i] != NULL)
	{
		cmp_i = -1;	
		while(++cmp_i < str_len)
			if (key[cmp_i] != envp[i][cmp_i])
				break;
		if (envp[i][cmp_i] == '=')
			return(i);
	}
	return (-1);
}

int	ms_getenv(char *key, char **envp)
{
	int	i;
	int	cmp_i;
	int	str_len;

	i = -1;
	str_len = strlen(key);
	while(envp[++i] != NULL)
	{
		cmp_i = -1;	
		while(++cmp_i < str_len)
			if (key[cmp_i] != envp[i][cmp_i])
				break;
		if (
	}
	return (0);
}
