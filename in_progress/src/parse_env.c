/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 13:05:00 by snpark            #+#    #+#             */
/*   Updated: 2021/10/06 11:32:29 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	parse_env(char ***original_envp)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * ARG_MAX);
	i = -1;
	while ((*original_envp)[++i] != NULL)
	{
		new_envp[i] = strdup((*original_envp)[i]);//replace strdup
		if (new_envp[i] == NULL)
			return (1);
	}
	new_envp[i] = NULL;
	*original_envp = new_envp;
	return(0);
}

/*
** Make char **env size ARG_MAX in limits.h
** fill last index NULL
*/
