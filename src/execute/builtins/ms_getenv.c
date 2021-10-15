/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:40:25 by snpark            #+#    #+#             */
/*   Updated: 2021/10/15 11:57:48 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_key_value_idx
	ms_getenv(char *key, char **envp)
{
	t_key_value_idx	idx;
	int	str_len;

	str_len = strlen(key);
	if (key[str_len] == '=')
		--str_len;
	idx.key = -1;
	while(envp[++idx.key] != NULL)
	{
		idx.value = -1;
		while(++idx.value < str_len)
			if (key[idx.value] != envp[idx.key][idx.value])
				break;
		if (envp[idx.key][idx.value] == '=')
		{
			++idx.value;
			return (idx);
		}
		if (envp[idx.key][idx.value] == '\0')
		{
			idx.value = -1;
			return (idx);
		}
	}
	idx.key = -1;
	idx.value = -1;
	return (idx);
}
