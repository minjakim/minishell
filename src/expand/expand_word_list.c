/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:50:21 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/27 18:03:43 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	expand_is_whitespace(const char *str)
{
	while (*str && (*str == ' ' || *str == '\t' || *str++ == '\n'))
		return (TRUE);
	return (FALSE);
}

//int
//	expand_get_index(const char *str)
//{
//	int	i;

//	i = -1;
//	while (str[++i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
//		return (i);
//	return (i);
//}


//static t_word_list
//	*expand_attach_word(t_word_list *words, char *word, int count)
//{
//	if (count == 0)
//	{
//		words->word.word = word;
//		words->next = NULL;
//		words->word.flags &= ~W_HASHDOLLAR;
//	}
//	else
//	{
//		words->next = xcalloc(sizeof(t_word_list));
//		words->next->word.word = word;
//		words->next->word.flags = words->word.flags;
//		words = words->next;
//	}
//	return (words);
//}

//int
//	expand_word_split(t_command *cmd, t_word_list *words, int argc)
//{
//	const char			*word = words->word.word;
//	const char			*temp = words->word.word;
//	const t_word_list	*next = words->next;
//	int					count;
//	int					i;

//	count = -1;
//	i = -1;
//	while (LOOP)
//	{
//		while (word[i] == ' ' || word[i] == '\t' || word[i] == '\n')
//			++i;
//		if (word[i] != '\0')
//		{
//			word = word + i;
//			i = expand_get_index(word);
//			words = expand_attach_word(words, ft_strndup() count);
//			++count;
//		}
//		}
//	}
//	if (count > -1)
//	{
//		xfree(temp);
//		words->next = next;
//		*argc += count;
//	}
//	return (SUCCESS);
//}

//int
//	expand_word_split(t_command *cmd, t_word_list *words, int argc)
//{
//	const char			*word = words->word.word;
//	const t_word_list	*next = words->next;
//	int					count;
//	int					i;

//	i = 0;
//	count = argc;
//	while (word[i])
//	{
//			if (word[i] == ' ' || word[i] == '\t' || word[i] == '\n')
//				++i;
//			if (word[i] == '\0')
//			{
//				word = word + i;
//				i = expand_get_index(word);
//				if (count == argc)
//					word =
//				words->next = xcalloc(sizeof(t_word_list));
//				words = words->next;
//			}
//		}
//			words->word.word = ft_strndup(line, i + 1);
//		++i;
//	}
//	return (SUCCESS);
//}
