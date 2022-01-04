/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:50:21 by minjakim          #+#    #+#             */
/*   Updated: 2022/01/04 17:21:46 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	expand_is_whitespace(const char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t' || *str++ == '\n')
			return (TRUE);
	}
	return (FALSE);
}

static int
	expand_get_word(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		++i;
	return (i);
}

static t_word_list
	*expand_attach_word(t_word_list *words, char *word, int count)
{
	if (count == 0)
	{
		words->word.word = word;
		words->next = NULL;
		words->word.flags &= ~W_HASHDOLLAR;
	}
	else
	{
		words->next = xcalloc(sizeof(t_word_list));
		words->next->word.word = word;
		words->next->word.flags = words->word.flags;
		words = words->next;
	}
	return (words);
}

static t_word_list
	*expand_split_word(t_command *cmd, t_word_list *words)
{
	const char	*word = words->word.word;
	int			count;
	int			i;

	count = -1;
	i = 0;
	while (word[i])
	{
		i += expand_get_word(word + i);
		if (word[i] != '\0')
		{
			word = word + i;
			i = 0;
			while (word[i] && \
					!(word[i] == ' ' || word[i] == '\t' || word[i] == '\n'))
				++i;
			++count;
			words = expand_attach_word(words, ft_strndup(word, i), count);
		}
	}
	cmd->argc += count;
	return (words);
}

t_word_list
	*expand_make_words(t_command *cmd, t_word_list *prev, t_word_list *words)
{
	t_word_list *const	next = words->next;
	char				*temp;

	if (words->word.word[expand_get_word(words->word.word)] == '\0')
	{
		disposer(words->word.word, words, NULL, NULL);
		--cmd->argc;
		if (prev == NULL)
			return (cmd->words = next);
		else
			prev->next = next;
		return (prev);
	}
	else
	{
		temp = words->word.word;
		words = expand_split_word(cmd, words);
		words->next = next;
		xfree(temp);
		return (words);
	}
}
