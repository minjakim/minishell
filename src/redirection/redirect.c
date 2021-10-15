/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:03 by snpark            #+#    #+#             */
/*   Updated: 2021/10/15 11:58:54 by minjakim         ###   ########.fr       */
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

	if (cmd->out_pipe == 1)//&& cmd->next->in_pipe == 1)
	{
		pipe(pipe_fd);
		cmd->out_pipe = pipe_fd[1];
		cmd->next->in_pipe = pipe_fd[0];
	}
	while (cmd->in_file != NULL)
	{
		if (cmd->in_file->redirection == 0b100)
			cmd->stream_in = open(cmd->in_file->file, O_RDONLY);
		if (cmd->in_file->redirection == 0b1000)
			cmd->stream_in = read_all_line(cmd->in_file->file);
		if ((cmd->in_file = cmd->in_file->next))
			close(cmd->stream_in);
	}
	while (cmd->out_file != NULL)
	{
		if (cmd->out_file->redirection == 2)
			cmd->stream_out = open(cmd->out_file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->out_file->redirection == 1)
			cmd->stream_out = open(cmd->out_file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((cmd->out_file = cmd->out_file->next))
			close(cmd->stream_out);
	}
	return (0);
}
