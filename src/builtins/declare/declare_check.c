/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:37:29 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 16:14:27 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int
	legal_variable_starter(const char c)
{
	return ((((unsigned)c | 32) - 97 < 26) || (c == '_')) ;
}

static int
	legal_variable_char(const char c)
{
	return ((((unsigned)c | 32) - 97 < 26) || ((unsigned)c - 48 < 10) \
			|| (c == '_'));
}

static int
	legal_identifier(const char *name)
{
	if (!legal_variable_starter(*name))
		return (FALSE);
	while (*++name)
		if (!legal_variable_char(*name))
			return (FALSE);
	return (TRUE);
}

//int
//	check_identifier (word, check_word)
//     WORD_DESC *word;
//     int check_word;
//{
//  if ((word->flags & (W_HASDOLLAR|W_QUOTED)) || all_digits (word->word))
//    {
//      internal_error (_("`%s': not a valid identifier"), word->word);
//      return (0);
//    }
//  else if (check_word && legal_identifier (word->word) == 0)
//    {
//      internal_error (_("`%s': not a valid identifier"), word->word);
//      return (0);
//    }
//  else
//    return (1);
//}

int
	assignment(const char *str)
{
	unsigned char	c;
	int				index;

	c = *str;
	index = 0;
	if (legal_variable_starter(c) == 0 || legal_identifier(str) == 0)
		return (0);
	while (str[index])
	{
		c = str[index];
		if (c == '=')
			return (index);
		if (c == '+' && str[index + 1] == '=')
			return (index + 1);
		if (legal_variable_char(c) == 0)
			return (0);
		++index;
	}
	return (0);
}
