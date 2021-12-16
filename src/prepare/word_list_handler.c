/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:31:06 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/16 10:02:22 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	line_is_exception(const char *line)
{
	int	result;

	result = 0;
	while (*line)
	{
		if ((*line == ';' || *line == '\\') && !result)
			return (*line);
		else if (is_quote(*line, result))
			result ^= *line;
		++line;
	}	
	return (result);
}

static int
	is_start(const char *const str, const int i, const int quote)
{
	if (quote)
		return (FALSE);
	if ((i == 0 || (str[i - 1] == ' ' || str[i - 1] == '\t' || \
					str[i - 1] == '<' || str[i - 1] == '>' || \
					str[i - 1] == '|' || str[i - 1] == '&')) && \
			(str[i] != ' ' && str[i] != '\t'))
		return (TRUE);
	if (((i == 0 || str[i - 1] != '<') && str[i] == '<') || \
			((i == 0 || str[i - 1] != '>') && str[i] == '>') || \
			((i == 0 || str[i - 1] != '|') && str[i] == '|') || \
			((i == 0 || str[i - 1] != '&') && str[i] == '&'))
		return (TRUE);
	return (FALSE);
}

static int
	is_end(const char *const str, int *i, const int quote)
{
	if (quote)
		return (FALSE);
	if ((str[*i] == '<' && str[*i + 1] == '<') || \
			(str[*i] == '>' && str[*i + 1] == '>') || \
			(str[*i] == '|' && str[*i + 1] == '|') || \
			(str[*i] == '&' && str[*i + 1] == '&'))
	{
		++(*i);
		return (TRUE);
	}
	if (str[*i] != ' ' && str[*i] != '\t' && \
			(str[*i + 1] == ' ' || str[*i + 1] == '\t' || \
			str[*i + 1] == '\0' || str[*i + 1] == '<' || \
			str[*i + 1] == '>' || str[*i + 1] == '|' || \
			str[*i + 1] == '&'))
		return (TRUE);
	if ((str[*i] == '<' && str[*i + 1] != '<') || \
			(str[*i] == '>' && str[*i + 1] != '>') || \
			(str[*i] == '|' && str[*i + 1] != '|'))
		return (TRUE);
	return (FALSE);
}

static int
	line_split(const char *line, t_word_list *words, char quote)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (is_start(line, i, quote))
		{
			line = line + i;
			i = 0;
			if (words->word.word != NULL)
			{
				words->next = xmalloc(sizeof(t_word_list));
				words = words->next;
				ft_memset(words, 0, sizeof(t_word_list));
			}
		}
		if (is_quote(line[i], quote))
			quote ^= line[i];
		if (is_end(line, &i, quote))
			words->word.word = ft_strndup(line, i + 1);
		i++;
	}
	return (SUCCESS);
}

t_word_list
	*word_list_handler(char *line)
{
	t_word_list	*result;

	if (line_is_exception(line))
		return (NULL);
	result = xmalloc(sizeof(t_word_list));
	result->next = NULL;
	result->word.word = NULL;
	result->word.flags = 0;
	if (!line_split(line, result, '\0'))
		return (word_list_free(result));
	if (word_list_flag(result) == EXCEPTION)
		return (word_list_free(result));
	return (result);
}
