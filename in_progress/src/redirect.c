/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:03 by snpark            #+#    #+#             */
/*   Updated: 2021/10/05 15:33:20 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
//void	stdout_to_file(char **argv, char **envp, int flag)
//{
//	int		fd;
//	int		file_fd;
//
//	file_fd = open("sample", flag, 0644);
//	(void)argv;
//	(void)envp;
//	(void)fd;
////	fd = fork();
////	if (fd == 0)
////	{
////		dup2(file_fd, 1);
////		shell_execve(argv[2], argv + 2, envp);
////	}
////	else if (fd > 0)
////	{
////		close(file_fd);
////		wait(NULL);
////	}
////	else
////	{
////		write(2, strerror(errno), strlen(strerror(errno)));
////		exit(errno);
////	}
//}
//
//void	file_to_stdin(char **argv, char **envp)
//{
//	int		fork_fd;
//
//	read_fd = open("sample", O_RDONLY); 
//	fork_fd = fork();
//	if (fork_fd > 0)
//	{
//		close(read_fd);
//		wait(NULL);
//	}
//	else if (fork_fd == 0)
//	{
//		dup2(read_fd, 0);
//	//	shell_execve(argv[2], argv + 2, envp);
//	}
//	else
//		;
//}
//
//void	stdin_to_stdin(char **argv, char **envp)
//{
//	int		pipe_fd[2];
//	int		fork_fd;
//	char	buffer[1024];
//	int		read_len;
//
//	//read from stdin
//	memset(buffer, '\0', 1024);
//	if (pipe(pipe_fd))
//		;//error
//	while ((read_len = read(0, buffer, 1024)))
//	{
//		if (read_len == -1)
//		{
//			if (errno == EINTR)//read intrupped by signal
//				continue;
//			//error
//		}
//		if (strcmp(buffer, "END\n") == 0)
//			break;
//		write(pipe_fd[1], buffer, read_len);
//		memset(buffer, '\0', 1024);
//	}
//	fork_fd = fork();
//	if(fork_fd > 0)
//	{
//		close(pipe_fd[0]);
//		close(pipe_fd[1]);
//		wait(NULL);
//	}
//	else if (fork_fd == 0)
//	{
//		close(pipe_fd[1]);
//		dup2(pipe_fd[0], 0);
//		//shell_execve(argv[2], argv + 2, envp);
//	}
//	else
//		;
//}
//
//void	stdout_to_stdin(char **argv, char **envp)
//{
//	int	pipe_fd[2];
//	int	fork_fd;
//	char *ls;
//	char *cat;
//	char buffer[1024];
//
//	ls = "ls";
//	cat = "cat";
//	pipe(pipe_fd);
//	fork_fd = fork();
//	if (fork_fd == 0)
//	{
//		dup2(pipe_fd[1], 1);
//		//shell_execve(argv[2], argv + 2, envp);
//	}
//	else if (fork_fd > 0)
//	{
//		wait(NULL);
//		write(1, "-------------------------------\n", 32);
//		memset(buffer, '\0', 1024);
//		read(pipe_fd[0], buffer, 1024);
//		write(1, buffer, 1024);
//		write(1, "-------------------------------\n", 32);
//		fork_fd = fork();
//		if (fork_fd == 0)
//		{
//			dup2(pipe_fd[0], 0);
//			argv[3] = NULL;
//			//shell_execve(cat, &cat, envp); 
//		}
//		else if (fork_fd > 0)
//		{
//			wait(NULL);
//			close(pipe_fd[0]);
//			close(pipe_fd[1]);
//		}
//		else
//			;
//	}
//	else
//		;
//
//}
*/


int	read_all(int src_fd, int dest_fd)
{
	char	buffer[1024];
	int		read_len;

	memset(buffer, '\0', 1024 * sizeof(char));
	while ((read_len = read(src_fd, buffer, 1024)))
	{
		if (read_len == -1)
		{
			if (errno == EINTR)//read intrupped by signal
				continue;
			else
				exit(1); //error
		}
		write(dest_fd, buffer, read_len);
		memset(buffer, '\0', 1024);
	}
	return (0);
}

int	read_all_line(int dest_fd, char *eof)
{
	char	*line;

	(void)eof;
	while ((line = readline("redirection> ")) && strcmp(line, eof))
		write(dest_fd, line, strlen(line));
	return (0);
}

int	redirect(t_command *cmd)
{
	int	file_fd;
	int	pipe_fd[2];

	if (cmd->out_pipe == 1)//&& cmd->next->in_pipe == 1)
	{
		pipe(pipe_fd);
		cmd->out_pipe = pipe_fd[1];
		cmd->next->in_pipe = pipe_fd[0];
	}
	if (cmd->in_file != NULL)
	{
		pipe(pipe_fd);
		cmd->stream_in = pipe_fd[0];
	}
	while (cmd->in_file != NULL)
	{
		if (cmd->in_file->redirection == 0b100)
		{
			file_fd = open(cmd->in_file->file, O_RDONLY); 		
			read_all(file_fd, pipe_fd[1]);
			close(file_fd);
		}
		if (cmd->in_file->redirection == 0b1000)
			read_all_line(pipe_fd[1], cmd->in_file->file);
		cmd->in_file = cmd->in_file->next;
	}
	if (cmd->stream_in != 0)
		close(pipe_fd[1]);
	while (cmd->out_file != NULL)
	{
		if (cmd->out_file->redirection == 2)
			file_fd = open(cmd->out_file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->out_file->redirection == 1)
			file_fd = open(cmd->out_file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		cmd->stream_out = file_fd;
		if (cmd->out_file->next != NULL)
			close(file_fd);
		cmd->out_file = cmd->out_file->next;
	}
	return (0);
}
