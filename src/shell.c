/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/11/13 20:40:27 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command
	*make_cmd(void)
{
	t_command	*cmd1;

	cmd1 = malloc(sizeof(t_command));
	if (!cmd1)
		exit(1);
	cmd1->argv = malloc(sizeof(char *) * 4);
	if (!cmd1->argv)
		exit(1);
	cmd1->argv[0] = "./cat";
	cmd1->argv[1] = NULL;
	cmd1->argv[2] = NULL;
	cmd1->argv[3] = NULL; 
	cmd1->stream.out = 1;
	cmd1->stream.in = 0;
	cmd1->pipe.in = -1;
	cmd1->pipe.out = -1;
	cmd1->next = NULL;
	cmd1->file.out = NULL;
	cmd1->file.in = NULL;
//	cmd1->file.in = malloc(sizeof(t_file));
//	cmd1->file.in->file = "notexitst";
//	cmd1->file.in->redirection = 0b100;
//	cmd1->file.in->next = NULL;
 //	cmd1->next = malloc(sizeof(t_command));
 //	cmd1->next->argv = malloc(sizeof(char *) * 2);
 //	cmd1->next->argv[0] = "exit";
 //	cmd1->next->argv[1] = NULL;
 //	cmd1->next->stream.out = 1;
 //	cmd1->next->stream.in = 0;
 //	cmd1->next->pipe.in = 1;
 //	cmd1->next->pipe.out = -1;
 //	cmd1->next->file.out = NULL;
 //	cmd1->next->file.in = NULL;
 //	cmd1->next->next = NULL;
//	if (!(cmd1->file.out = malloc(sizeof(t_file))))
//		exit(1);
//	cmd1->file.out->file = "out.txt";
//	cmd1->file.out->redirection = 1;//> out.txt
//	cmd1->file.out->next = NULL;
//	if (!(cmd1->file.in = malloc(sizeof(t_file))))
//		exit(1);
//	cmd1->file.in->file = "eof";
//	cmd1->file.in->redirection = 0b1000;//<< eof
//	cmd1->file.in->next = NULL;
	return (cmd1);
}

//int
//	main(int argc, char **argv, char **envp)
//{
//	t_command	*cmd_list;
//	t_command	*cmd_handle;
//	int			count;

//	cmd_list = make_cmd();
//	(void)&argc;
//	(void)argv;
//	if (parse_env(&envp))
//		return(1);
//	cmd_handle = cmd_list;
//	count = 0;
//	while (cmd_handle != NULL)
//	{
//		redirect(cmd_handle);
//		cmd_handle = cmd_handle->next;
//		printf("count %d\n", ++count);
//	}
//	printf("redirection part done\n");
//	cmd_handle = cmd_list;
//	count = 0;
//	while (cmd_handle != NULL)
//	{
//		shell_execve(*cmd_handle, envp);
//		cmd_handle = cmd_handle->next;
//		printf("----------\ncnt %d\n", ++count);
//	}
//}
