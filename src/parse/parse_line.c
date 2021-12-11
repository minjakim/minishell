/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:31:06 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/11 19:02:34 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	is_exception(char *line)
{
	int	result;

	result = 0;
	while (*line)
	{
		if ((*line == ';' || *line == '\\') && !result)
			return (*line);
		else if (*line == '\'' || *line == '\"')
		{
			result ^= *line;
			if (result == 5)
				result ^= *line;
		}
		++line;
	}
	return (result);
}

static int
	add_word_list(t_word_list *words, char *line)
{
	t_word_list *new_node;

	if (words->word.word == NULL)
		words->word.word = line;
	else
	{
		new_node = malloc(sizeof(t_word_list));
		if (!new_node)
			return (FAIL);
		new_node->next = NULL;
		new_node->word.word = line;
		words->next = new_node;
	}
	return (SUCCESS);
}

static int
	split_line(char *line, t_word_list *words, char temp)
{
	while (*line)
	{
		while (*line == ' ' || *line == '\t')
			*line++ = '\0';
		if (*line == '\0')
			return (SUCCESS);
		if (!add_word_list(words, line))
			return (FAIL);
		if (words->next != NULL)
		{
			words = words->next;
			words->word.flags |= W_ARG;
		}
		while (*line && *line != ' ' && *line != '\t')
		{
			if (*line == '\'' || *line == '\"')
			{
				temp = *line++;
				while (*line != temp)
					++line;
			}
			++line;
		}
	}
	return (SUCCESS);
}

//static int
//	flag_word(t_word_list *words)
//{
//	int		i;
//	int		quote;
//
//	while (words)
//	{
//		i = 0;
//		quote = 0;
//		while (words->word.word[i])
//		{
//			if (is_quote(words->word.word[i], quote))
//			{
//				quote ^= words->word.word[i];
//				if (quote == '\"')
//					words->word.flags |= W_DQUOTED;
//				else if (quote == '\'')
//					words->word.flags |= W_QUOTED;
//			}
//			if (words->word.word[i] && is_key(words->word.word, i, quote))
//				words->word.flags |= W_HASHDOLLAR;
//			++i;
//		}
//		words = words->next;
//	}
//}

t_word_list
	*parse_line(char *line)
{
	t_word_list	*words;

	if (is_exception(line))
		return (NULL);
	words = malloc(sizeof(t_word_list));
	if (!words)
		return (NULL);
	words->next = NULL;
	words->word.word = NULL;
	words->word.flags |= W_ARG;
	if (!split_line(line, words, '\0'))
		return (NULL);
//	flag_word(buffer->words);
	return (words);
}
