/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:31:06 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/22 19:53:55 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static inline int
	word_is_end(const char *const str, int *i, const int quote)
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

static inline int
	word_is_start(const char *const str, const int i, const int quote)
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
	line_split(const char *line, t_word_list *words, char quote)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (word_is_start(line, i, quote))
		{
			line = line + i;
			i = 0;
			if (words->word.word != NULL)
			{
				words->next = xcalloc(sizeof(t_word_list));
				words = words->next;
			}
		}
		if (is_quote(line[i], quote))
			quote ^= line[i];
		if (word_is_end(line, &i, quote))
			words->word.word = ft_strndup(line, i + 1);
		++i;
	}
	return (SUCCESS);
}

static int
	line_is_exception(const char *line)
{
	char	result;

	result = '\0';
	while (*line)
	{
		if ((*line == ';' || *line == '\\') && !result)
			return (report_error_syntax(line));
		else if (is_quote(*line, result))
			result ^= *line;
		++line;
	}
	if (result)
		report_error_syntax(&result);
	return (result);
}

t_word_list
	*parse_line(char *line)
{
	t_word_list	*words;

	if (line_is_exception(line))
		return (NULL);
	words = xcalloc(sizeof(t_word_list));
	if (!line_split(line, words, '\0'))
		return (dispose_words(words));
	if (words->word.word == NULL)
		words->word.word = ft_strdup("");
	if (make_words(words) == EXCEPTION)
		return (dispose_words(words));
	return (words);
}
