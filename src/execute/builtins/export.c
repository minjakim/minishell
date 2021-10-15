/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:30:50 by snpark            #+#    #+#             */
/*   Updated: 2021/10/15 11:57:48 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	find_offset(char *str)
{
	int	i;

	if (str == NULL || *str == '\0')
		return (-1);
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
		return (i);
	return (-1);
}

int
	ms_export(char **argv, char **envp, int stream_in, int stream_out)
{
	t_key_value_idx idx;
	int				offset;
	int				i;
	(void)argv;
	(void)envp;
	(void)stream_in;
	(void)stream_out;

	if (argv == NULL || argv[1] == NULL)
		exit(1);
	offset = find_offset(argv[1]);
	if (offset == -1)
		exit(1);/*no '=' in str*/
	argv[1][offset] = '\0';
	idx = ms_getenv(argv[1], envp);
	argv[1][offset] = '=';
	if (idx.key == -1)
	{
		i = -1;
		while (envp[++i] != NULL)
			;
		envp[i] = strdup(argv[1]);
	}
	else
	{
		free(envp[idx.key]);
		envp[idx.key] = strdup(argv[1]);
	}
	return (1);
}
