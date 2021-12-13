/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:44:39 by snpark            #+#    #+#             */
/*   Updated: 2021/12/13 12:14:07 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void
	envp_free(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}

static int
	envp_len(t_declare *handle)
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
	envp_make(char **new_envp, t_declare *handle)
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
				return (FAILURE);
			strcat(strcat(ft_strcpy(new_envp[i], handle->key), "="), \
					handle->value);
			++i;
		}
		handle = handle->next;
	}
	return (SUCCESS);
}

int
	envp_update(t_env *env, int flag)
{
	extern char	**environ;
	const int	envplen = envp_len(env->declare);
	char		**new_envp;
	int			i;

	new_envp = malloc(sizeof(char *) * (envplen + 2));
	if (new_envp == NULL)
		return (FAILURE);
	ft_memset(new_envp, 0, envplen + 2);
	if (!envp_make(new_envp, env->declare))
		return (FAILURE);
	if (flag == 1)
		envp_free(env->envp);
	env->envp = new_envp;
	environ = new_envp;
	return (SUCCESS);
}

static int
	declare_env(t_env *env)
{
	int		i;
	char	*temp;

	i = -1;
	while (env->envp[++i])
	{
		temp = ft_strdup(env->envp[i]);
		if (temp == NULL)
			return (FAILURE);
		if (declare_add(&env->declare, temp, H_EXPORT) != 0)
			return (FAILURE);
		free(temp);
	}
	return (SUCCESS);
}

int
	handler_envp(t_env *env)
{
	if (!declare_env(env))
		return (FAILURE);
	if (!envp_update(env, 0))
		return (FAILURE);
	return (SUCCESS);
}

static void
	declare_free(t_declare *temp)
{
	free(temp->key);
	free(temp->value);
	free(temp);
}

static t_declare
	*declare_check_key(t_declare *head, const char *const key)
{
	t_declare	*back;
	t_declare	*handle;

	handle = head;
	back = handle;
	while (handle)
	{
		if (*key == *handle->key && ft_strcmp(key, handle->key) == 0)
			return (back);
		if (ft_strcmp(key, handle->key) < 0)
			return (back);
		back = handle;
		handle = handle->next;
	}
	return (back);
}

static int
	declare_make_head(t_declare **head, t_declare *back, t_declare temp)
{
	t_declare	*new;

	new = malloc(sizeof(t_declare));
	if (new == NULL)
		return (1);
	ft_memset(new, 0, sizeof(t_declare));
	new->flag = temp.flag;
	*head = new;
	new->next = back;
	new->key = ft_strdup(temp.key);
	if (new->key == NULL)
		return (1);
	if (new->flag & H_KEYONLY)
		new->value = NULL;
	else
	{
		new->value = ft_strdup(temp.value);
		if (new->value == NULL)
			return (1);
	}
	return (0);
}

static int
	declare_make(t_declare *back, t_declare temp)
{
	t_declare	*new;

	new = malloc(sizeof(t_declare));
	if (new == NULL)
		return (1);
	ft_memset(new, 0, sizeof(t_declare));
	new->flag = temp.flag;
	new->next = back->next;
	back->next = new;
	new->key = ft_strdup(temp.key);
	if (new->key == NULL)
		return (1);
	if (new->flag & H_KEYONLY)
		new->value = NULL;
	else
	{
		new->value = ft_strdup(temp.value);
		if (new->value == NULL)
			return (1);
	}
	return (0);
}

static int
	declare_add_unit(t_declare **head, t_declare *back, t_declare temp)
{
	if (back && back->next && ft_strcmp(temp.key, back->next->key) == 0 \
			&& temp.value == NULL)
		return (0);
	else if (back && back->next && ft_strcmp(temp.key, back->next->key) == 0)
		return (declare_edit(temp.value, back->next, temp.flag));
	else if (back == NULL || (back && ft_strcmp(temp.key, back->key) < 0))
		return (declare_make_head(head, back, temp));
	else
		return (declare_make(back, temp));
	return (1);
}

int
	declare_add(t_declare **head, char *str, int flag)
{
	int		offset;
	t_declare	temp;

	//offset = assignment(str);
	//if (offset == 0)
	//	return (1);
	if (str[offset - 1] == '+')
	{
		str[offset - 1] = '\0';
		flag |= H_CAT;
	}
	if (offset != 0)
		str[offset] = '\0';
	temp.key = str;
	temp.value = str + offset + 1;
	if (offset == 0)
	{
		temp.value = NULL;
		flag |= H_KEYONLY;
	}
	temp.flag = flag;
	declare_check_key(*head, temp.key);
	return (declare_add_unit(head, declare_check_key(*head, temp.key), temp));
}

int
	declare_remove(t_declare **head, const char *const key)
{
	t_declare	*back;

	if (*head == NULL || key == NULL)
		return (0);
	back = declare_check_key(*head, key);
	if (back == *head && ft_strcmp(key, back->key) == 0)
	{
		*head = back->next;
		declare_free(back);
	}
	if (back->next && ft_strcmp(key, back->next->key) == 0)
	{
		back->next = back->next->next;
		declare_free(back->next);
	}
	return (0);
}
