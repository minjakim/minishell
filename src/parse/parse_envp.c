/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:06:54 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 11:12:58 by snpark           ###   ########.fr       */
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
					* (strlen(handle->key) + ft_strlen(handle->value) + 2));
			if (new_envp[i] == NULL)
				return (1);
			strcat(strcat(strcpy(new_envp[i], handle->key), "="), \
					handle->value);
			++i;
		}
		handle = handle->next;
	}
	return (0);
}

static int
	declare_env(t_env *env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env->envp[++i])
	{
		tmp = strdup(env->envp[i]);
		if (tmp == NULL)
			return (1);
		if (declare_add(&env->declare, tmp, H_EXPORT) != 0)
			return (1);
		free(tmp);
	}
	return (0);
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
		return (1);
	ft_memset(new_envp, 0, envp_len + 2);
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
