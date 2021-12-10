/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:31:06 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/10 12:55:39 by snpark           ###   ########.fr       */
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
	add_word_list(t_word_list *node, char *line)
{
	t_word_list *new_node;

	if (node->word.word == NULL)
		node->word.word = line;
	else
	{
		new_node = malloc(sizeof(t_word_list));
		if (!new_node)
			return (0);
		new_node->next = NULL;
		new_node->word.word = line;
		node->next = new_node;
	}
	return (1);
}

static int
	split_line(char *line, t_word_list *node, char temp)
{
	while (*line)
	{
		while (*line == ' ' || *line == '\t')
			*line++ = '\0';
		if (*line == '\0')
			return (SUCCESS);
		if (!add_word_list(node, line))
			return (EXCEPTION);
		if (node->next != NULL)
		{
			node = node->next;
			node->word.flags |= W_ARG;
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
//	flag_word(t_word_list *node)
//{
//	int		i;
//	int		quote;
//
//	while (node)
//	{
//		i = 0;
//		quote = 0;
//		while (node->word.word[i])
//		{
//			if (is_quote(node->word.word[i], quote))
//			{
//				quote ^= node->word.word[i];
//				if (quote == '\"')
//					node->word.flags |= W_DQUOTED;
//				else if (quote == '\'')
//					node->word.flags |= W_QUOTED;
//			}
//			if (node->word.word[i] && is_key(node->word.word, i, quote))
//				node->word.flags |= W_HASHDOLLAR;
//			++i;
//		}
//		node = node->next;
//	}
//}

int
	parse_line(t_buffer *buffer)
{
	if (is_exception(buffer->line))
		return (EXCEPTION);
	buffer->node = malloc(sizeof(t_word_list));
	buffer->node->next = NULL;
	buffer->node->word.word = NULL;
	
	buffer->node->word.flags |= W_ARG;
	split_line(buffer->line, buffer->node, '\0');
//	flag_word(buffer->node);
	return (SUCCESS);
}
