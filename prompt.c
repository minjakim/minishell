/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:27:29 by snpark            #+#    #+#             */
/*   Updated: 2021/09/18 16:29:56 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	eof(char *line)
{
	if (line == NULL)
		return (1);
	return(0);
}

int
	append_line(char **line, char buf)
{
	char	*dest;
	int		len;

	len = strlen(*line);
	dest = malloc(sizeof(char) * (len + 2));
	strcpy(dest, *line);
	dest[len] = buf;
	dest[len + 1] = '\0';
	if (*line != NULL)
		free(*line);
	*line = dest;
	return (0);
}

int
	prompt(char	**line)
{
	char	buffer;
	int		read_len;

	write(1, "$> ", 3);
	if (*line != NULL);
	{
		free(*line);
		*line = NULL;
	}
	while ((read_len = read(0 , &buffer, 1)) != -1)
	{
		if (read_len == 0)
			return (eof(*line));
		if (buffer != '\n')
			append_line(line, buffer);
		if (buffer == '\n')
			return (0);
	}
}
