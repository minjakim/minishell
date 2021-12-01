/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:06:54 by snpark            #+#    #+#             */
/*   Updated: 2021/12/01 18:07:04 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char **environ;

static int
	declare_env(t_env *env)
{
	int		i;
	char	*tmp;

	i = -1;
	while(env->envp[++i])
	{
		tmp = strdup(env->envp[i]);
		if (tmp == NULL)
			return (1);
		if (add_declare(&env->declare, tmp, H_EXPORT) != 0)
			return (1);
		free(tmp);
	}
	return (0);
}

int
	replace_envp(t_env *env, int flag)
{
	char			**new_envp;
	t_hash			*handle;
	const int		envp_len = envplen(env->declare);
	int				i;

	new_envp = malloc(sizeof(char *) * (envp_len + 2));
	if (new_envp == NULL)
		return (1);
	memset(new_envp, 0, envp_len + 2); 
	if (make_envp(new_envp, env->declare) != 0)
		return (1);
	if (flag == 1)
		free_envp(env->envp);
	env->envp = new_envp;
	environ = new_envp;
	return (0);
}

int
	parse_envp(t_env *env)
{
	if (declare_env(env) != 0)
		return (1);
	if (replace_envp(env, 0) != 0)
		return (1);
	return (0);
}
