/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/12/01 17:31:30 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include <string.h>

int	g_exit_status;

int main(int argc, char **argv, char **envp)
{
	t_shell		mini;

	(void)&argc;
	(void)argv;
	mini.env.envp = envp;
	initialize(&mini);
	char *tmp = strdup("qwe");
	printf("%d\n", add_declare(&mini.env.declare, tmp, 1));
	replace_envp(&mini.env, 1);
	free(tmp);
	print_export(mini.env.declare);
	tmp = strdup("NAME=snpark hello");
	printf("%d\n", add_declare(&mini.env.declare, tmp, 1));
	replace_envp(&mini.env, 1);
	free(tmp);
	print_export(mini.env.declare);
	printf("%s\n", getenv("NAME"));
	return (0);
}
