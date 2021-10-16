/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/10/15 21:12:13 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int
	main(int argc, char **argv, char **envp)
{
	t_command	*cmd_list;
	t_command	*cmd_handle;

	(void)&argc;
	(void)argv;
	if (parse_env(&envp))//malloc and duplicate envp
		return(1);
	//signalsetting
	//readlinesetting
	while (1)
	{
		//buffer = readline();
		//cmd_list = parser();
		/*set redirection*/
		cmd_handle = cmd_list;
		while (cmd_handle != NULL)
		{
			redirect(cmd_handle);
			cmd_handle = cmd_handle->next;
		}
		/*execute cmd*/
		cmd_handle = cmd_list;
		while (cmd_handle != NULL)
		{
			/*$sign 해석을 이곳에서 해야함*/
			shell_execve(*cmd_handle, envp);
			cmd_handle = cmd_handle->next;
		}
	}
}
