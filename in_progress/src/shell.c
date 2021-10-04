/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/10/04 11:17:12 by snpark           ###   ########.fr       */
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
	cmd1->argv[1] = strdup("power is power");
	cmd1->argv[2] = NULL;
	cmd1->stream_out = 1;
	cmd1->stream_in = 0;
	cmd1->pipe = 0;
	cmd1->next = NULL;
	if (!(cmd1->out_file = malloc(sizeof(t_file))))
		exit(1);
	cmd1->out_file->file = "good.txt";
	cmd1->out_file->redirection = 2;
	cmd1->out_file->next = NULL;
	cmd1->in_file = NULL;
//	if (!(cmd1->in_file = malloc(sizeof(t_file))))
//		exit(1);
//	cmd1->in_file->file = "bazinga.txt";
//	cmd1->in_file->redirection = 0b100;
//	cmd1->in_file->next = NULL;
//	if (!(cmd1->in_file->next = malloc(sizeof(t_file))))
//		exit(1);
//	cmd1->in_file->next->file = "end";
//	cmd1->in_file->next->redirection = 0b1000;
//	cmd1->in_file->next->next = NULL;
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
	shell_execve(cmd_list[0], envp);
	//redirect(argv, envp);
//	set_signal();
//	while(42)
//	{
//		line = readline();
//		if (readline == NULL)
//			exit();
//	}"
}
