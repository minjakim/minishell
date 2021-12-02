/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/02 21:15:58 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include <string.h>

int	g_exit_status;

int main(int argc, char **argv, char **envp)
{
	t_shell		mini;

	(void)argc;
	(void)argv;
	mini.env.envp = envp;
	if (initialize(&mini) != 0)
		return (1);
	if (minishell(&mini) != 0)
		return (1);
	return (0);
}
