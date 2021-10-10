/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:30:50 by snpark            #+#    #+#             */
/*   Updated: 2021/10/06 20:56:22 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export(char **argv, char **envp, int stream_in, int stream_out)
{
	(void)argv;
	(void)envp;
	(void)stream_in;
	(void)stream_out;

	if (argv != NULL && argv[1] != NULL)
	{

	}
	return (0);
}
