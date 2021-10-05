/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/10/05 17:39:31 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*make_cmd(void)
{
	t_command	*cmd1;
	t_command	*cmd2;

	cmd1 = malloc(sizeof(t_command));
	if (!cmd1)
		exit(1);
	cmd1->argv = malloc(sizeof(char *) * 3);
	if (!cmd1->argv)
		exit(1);
	cmd1->argv[0] = strdup("echo");
	cmd1->argv[1] = strdup("fuck you");
	cmd1->argv[2] = NULL;
	cmd1->stream_out = 1;
	cmd1->stream_in = 0;
	cmd1->in_pipe = 0;
	cmd1->out_pipe = 1;
//	if (!(cmd1->out_file = malloc(sizeof(t_file))))
//		exit(1);
//	cmd1->out_file->file = "good.txt";
//	cmd1->out_file->redirection = 1;
//	cmd1->out_file->next = NULL;
	cmd1->in_file = NULL;
	cmd1->out_file = NULL;
//	if (!(cmd1->in_file = malloc(sizeof(t_file))))
//		exit(1);
//	cmd1->in_file->file = "./txt/bazinga.txt";
//	cmd1->in_file->redirection = 0b100;
//	cmd1->in_file->next = NULL;
//	if (!(cmd1->in_file->next = malloc(sizeof(t_file))))
//		exit(1);
//	cmd1->in_file->next->file = "end";
//	cmd1->in_file->next->redirection = 0b1000;
//	cmd1->in_file->next->next = NULL;
	if (!(cmd2 = malloc(sizeof(t_command))))
		exit(1);
	cmd1->next = cmd2;
	if (!(cmd2->argv = malloc(sizeof(char *) * 2)))
		exit(1);
	cmd2->argv[0] = "cat";//strdup("cat");
	cmd2->argv[1] = NULL;
	cmd2->out_file = NULL;
	if (!(cmd2->in_file = malloc(sizeof(t_file))))
		exit(1);
	cmd2->in_file->file = "good.txt";
	cmd2->in_file->redirection = 0b100;
	cmd2->in_file->next = NULL;
	cmd2->stream_out = 1;
	cmd2->stream_in = 0;
	cmd2->in_pipe = 1;
	cmd2->out_pipe = 0;
	cmd2->next = NULL;
	return (cmd1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*cmd_list;
	t_command	*cmd_handle;

	cmd_list = make_cmd();
	(void)&argc;
	(void)argv;
	if (parse_env(&envp))
		return(1);
	cmd_handle = cmd_list;
	while (cmd_handle != NULL)
	{
		redirect(cmd_handle);
		cmd_handle = cmd_handle->next;
	}
	cmd_handle = cmd_list;
	while (cmd_handle != NULL)
	{
		shell_execve(*cmd_handle, envp);
		cmd_handle = cmd_handle->next;
	}
}
