/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:03 by snpark            #+#    #+#             */
/*   Updated: 2021/11/13 20:42:25 by snpark           ###   ########.fr       */
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
	is_end(char **line, char *eof)
{
	*line = readline("redirection> ");
	if (*line && strcmp(*line, eof))
		return (1);
	return (0);
}

int
	read_all_line(char *eof)
{
	char	*line;
	t_io	io;

	line = NULL;
	pipe(io.fd);
	while (is_end(&line, eof))
	{
		write(io.fd[1], line, strlen(line));
		write(io.fd[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(io.fd[1]);
	return (io.fd[0]);
}

int
	redirect(t_command *cmd, int *exit_status)
{
	while (cmd->file.in != NULL)
	{
		if (cmd->file.in->redirection == 0b100)
			cmd->stream.in = open(cmd->file.in->file, O_RDONLY);
		if (cmd->file.in->redirection == 0b1000)
			cmd->stream.in = read_all_line(cmd->file.in->file);
		if (cmd->stream.in == -1)
		{
			*exit_status = 1;
			bash_arg_err(cmd->file.in->file);
			return (-1);
		}
		cmd->file.in = cmd->file.in->next;
		if (cmd->file.in)
			close(cmd->stream.in);
	}
	while (cmd->file.out != NULL)
	{
		if (cmd->file.out->redirection == 2)
			cmd->stream.out = open(cmd->file.out->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->file.out->redirection == 1)
			cmd->stream.out = open(cmd->file.out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		cmd->file.out = cmd->file.out->next;
		if (cmd->file.out)
			close(cmd->stream.out);
	}
	return (0);
}
