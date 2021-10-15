/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:03 by snpark            #+#    #+#             */
/*   Updated: 2021/10/15 12:18:58 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
**int	read_all(int src_fd, int dest_fd)
**{
**	char	buffer[1024];
**	int		read_len;
**
**	memset(buffer, '\0', 1024 * sizeof(char));
**	while ((read_len = read(src_fd, buffer, 1024)))
**	{
**		if (read_len == -1)
**		{
**			if (errno == EINTR)//read intrupped by signal
**				continue;
**			else
**				exit(1); //error
**		}
**		write(dest_fd, buffer, read_len);
**		memset(buffer, '\0', 1024);
**	}
**	return (0);
**}
*/

int
	read_all_line(char *eof)
{
	char	*line;
	int		pipe_fd[2];

	line = NULL;
	pipe(pipe_fd);
	while ((line = readline("redirection> ")) && strcmp(line, eof))
	{
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int
	redirect(t_command *cmd)
{
	int	pipe_fd[2];

	if (cmd->pipe.out == 1)//&& cmd->next->pipe.in == 1)
	{
		pipe(pipe_fd);
		cmd->pipe.out = pipe_fd[1];
		cmd->next->pipe.in = pipe_fd[0];
	}
	while (cmd->file.in != NULL)
	{
		if (cmd->file.in->redirection == 0b100)
			cmd->stream.in = open(cmd->file.in->file, O_RDONLY);
		if (cmd->file.in->redirection == 0b1000)
			cmd->stream.in = read_all_line(cmd->file.in->file);
		if ((cmd->file.in = cmd->file.in->next))
			close(cmd->stream.in);
	}
	while (cmd->file.out != NULL)
	{
		if (cmd->file.out->redirection == 2)
			cmd->stream.out = open(cmd->file.out->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->file.out->redirection == 1)
			cmd->stream.out = open(cmd->file.out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((cmd->file.out = cmd->file.out->next))
			close(cmd->stream.out);
	}
	return (0);
}
