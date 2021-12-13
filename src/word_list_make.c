/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_make.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:31:06 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/13 12:14:07 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int
	line_is_exception(char *line)
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
	word_list_add(t_word_list *words, char *line)
{
	t_word_list *new_node;

	if (words->word.word == NULL)
		words->word.word = line;
	else
	{
		new_node = malloc(sizeof(t_word_list));
		if (!new_node)
			return (FAILURE);
		new_node->next = NULL;
		new_node->word.word = line;
		words->next = new_node;
	}
	return (SUCCESS);
}

static int
	line_split(char *line, t_word_list *words, char temp)
{
	while (*line)
	{
		while (*line == ' ' || *line == '\t')
			*line++ = '\0';
		if (*line == '\0')
			return (SUCCESS);
		if (!word_list_add(words, line))
			return (FAILURE);
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
//	line_parse()
//{
//	return (0);
//}

t_word_list
	*word_list_make(char *line)
{
	t_word_list	*result;

	if (line_is_exception(line))
		return (NULL);
	result = malloc(sizeof(t_word_list));
	if (!result)
		return (NULL);
	result->next = NULL;
	result->word.word = NULL;
	result->word.flags |= W_ARG;
	if (!line_split(line, result, '\0'))
		return (NULL);
//	flag_word(buffer->result);
	return (result);
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
