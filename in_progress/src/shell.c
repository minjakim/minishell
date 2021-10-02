/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/10/02 18:52:40 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*make_cmd(void)
{
	t_command	*cmd1;

	cmd1 = malloc(sizeof(t_command));
	if (!cmd1)
		exit(1);
	cmd1->argv = malloc(sizeof(char *) * 3);
	if (!cmd1->argv)
		exit(1);
	cmd1->argv[0] = strdup("echo");
	cmd1->argv[1] = strdup("Come and Get");
	cmd1->argv[2] = NULL;
	cmd1->stream_out = 1;
	cmd1->stream_in = 0;
	cmd1->pipe = 0;
	cmd1->next = NULL;
	if (!(cmd1->out_file = malloc(sizeof(t_file))))
		exit(1);
	cmd1->out_file->file = "nothing_in_here.txt";
	cmd1->out_file->redirection = 1;
	if (!(cmd1->out_file->next = malloc(sizeof(t_file))))
		exit(1);
	cmd1->out_file->next->file = "bazinga.txt";
	cmd1->out_file->next->redirection = 1;
	cmd1->out_file->next->next = NULL;
	return (cmd1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*cmd_list;

	cmd_list = make_cmd();
	(void)&argc;
	(void)argv;
	if (parse_env(&envp))
		return(1);
	//parse_argv(); to NULL
	//signal setting
	//parse_prompt;
	//run_command();
	//check redirection with argv[1]
	redirect(cmd_list);
	shell_execve(cmd_list->argv[0], cmd_list->argv, envp);
	//redirect(argv, envp);
//	set_signal();
//	while(42)
//	{
//		line = readline();
//		if (readline == NULL)
//			exit();
//	}
}
