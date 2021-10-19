/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:17:50 by minjakim          #+#    #+#             */
/*   Updated: 2021/10/19 08:58:10 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//            "asdasdasd"
//return (((unsigned)c | 32) - 97 < 26);
//return (((unsigned)c | 5) - 39 < 1);

static int
	is_exception(char *line)
{
	while (*line)
		;
	return (0);
}


static int
	get_argc(char *line)
{
	int		count;
	char	unclosed;

	count = 0;
	unclosed = '\0';
	while (*line)
	{
		while (*line == ' ')
			++line;
		if (*line == '\0')
			break ;
		++count;
		while (*line != ' ' && *line != '\'' && *line != '\"')
			++line;
		if (!*line || *line != '\'' || *line != '\"')
			continue ;
		unclosed = *line++;
		while (*line != unclosed)
			;
	}
	return (count);
}

int
	parse_line(char *line)
{
	get_argc(line);

	return (0);
}
