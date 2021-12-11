/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:06:54 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 15:08:07 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void
	free_envp(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}

static int
	envplen(t_hash *handle)
{
	int		envp_len;

	envp_len = 0;
	while (handle)
	{
		if (handle->flag & H_EXPORT && !(handle->flag & H_KEYONLY))
			++envp_len;
		handle = handle->next;
	}
	return (envp_len);
}

static int
	make_envp(char **new_envp, t_hash *handle)
{
	int	i;

	i = 0;
	while (handle)
	{
		if (handle->flag & H_EXPORT && !(handle->flag & H_KEYONLY))
		{
			new_envp[i] = malloc(sizeof(char) \
					* (ft_strlen(handle->key) + ft_strlen(handle->value) + 2));
			if (new_envp[i] == NULL)
				return (FAIL);
			strcat(strcat(ft_strcpy(new_envp[i], handle->key), "="), \
					handle->value);
			++i;
		}
		handle = handle->next;
	}
	return (SUCCESS);
}

static int
	declare_env(t_env *env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env->envp[++i])
	{
		tmp = ft_strdup(env->envp[i]);
		if (tmp == NULL)
			return (FAIL);
		if (declare_add(&env->declare, tmp, H_EXPORT) != 0)
			return (FAIL);
		free(tmp);
	}
	return (SUCCESS);
}

int
	replace_envp(t_env *env, int flag)
{
	extern char	**environ;
	const int	envp_len = envplen(env->declare);
	char		**new_envp;
	int			i;

	new_envp = malloc(sizeof(char *) * (envp_len + 2));
	if (new_envp == NULL)
		return (FAIL);
	ft_memset(new_envp, 0, envp_len + 2);
	if (!make_envp(new_envp, env->declare))
		return (FAIL);
	if (flag == 1)
		free_envp(env->envp);
	env->envp = new_envp;
	environ = new_envp;
	return (SUCCESS);
}

int
	parse_envp(t_env *env)
{
	if (!declare_env(env))
		return (FAIL);
	if (!replace_envp(env, 0))
		return (FAIL);
	return (SUCCESS);
}
