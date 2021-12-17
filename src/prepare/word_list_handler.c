/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:31:06 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/17 20:23:06 by minjakim         ###   ########.fr       */
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

static int
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
	int		i;

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
	is_heredoc_max(t_word_list *words)
{
	int	count;

	count = 0;
	while (words)
	{
		if (words->word.flags & W_HEREDOC)
			++count;
		words = words->next;
	}
	if (count > HEREDOC_MAX)
	{
		g_status.exit = EX_BADUSAGE;
		exception_report(NULL, NULL, EX_HEREDOC_MAX, EX_BADUSAGE);
		return (TRUE);
	}
	return (FALSE);
}

t_word_list
	*word_list_handler(char *line)
{
	t_word_list	*result;

	if (line_is_exception(line))
		return (NULL);
	result = xcalloc(sizeof(t_word_list));
	if (!line_split(line, result, '\0'))
		return (word_list_free(result));
	if (word_list_flag(result) == EXCEPTION)
		return (word_list_free(result));
	if (is_heredoc_max(result))
		return (word_list_free(result));
	return (result);
}
