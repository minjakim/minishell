/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:56:06 by snpark            #+#    #+#             */
/*   Updated: 2021/12/27 18:43:36 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char
	*remove_quote(char *str)
{
	int		quote;
	char	*dest;

	quote = 0;
	dest = str;
	while (*str)
	{
		if (is_quote(*str, quote))
		{
			quote ^= *str;
			ft_strmove(str, str + 1, ft_strlen(str + 1));
		}
		else
			++str;
	}
	return (dest);
}

static int
	is_ambiguas(char *filename, t_redirect *redirects, int flags)
{
	if (!filename || !*filename || \
					(expand_is_whitespace(filename) && (flags & W_HASHDOLLAR)))
	{
		report_exception(NULL, redirects->redirectee.filename.word, \
				EX_AMBIGUAS, GENERAL_ERROR);
		if (filename)
			xfree(filename);
		return (FAILURE);
	}
	xfree(redirects->redirectee.filename.word);
	redirects->redirectee.filename.word = filename;
	return (SUCCESS);
}

static int
	expand_filename(t_redirect *redirects)
{
	char			*filename;
	int				flags;

	while (redirects)
	{
		filename = ft_strdup(redirects->redirectee.filename.word);
		flags = redirects->redirectee.filename.flags;
		if ((flags & (W_HASHDOLLAR | W_EXITSTATUS)) && \
			!(flags & W_NOEXPAND))
			filename = expand_str(filename, FALSE);
		if ((flags & W_GLOBEXP) && !(flags & W_NOEXPAND))
			filename = expand_glob_filename(filename);
		if (!is_ambiguas(filename, redirects, flags))
			return (FAILURE);
		remove_quote(redirects->redirectee.filename.word);
		redirects = redirects->next;
	}
	return (SUCCESS);
}

static int
	expand_argv(t_command *cmd)
{
	t_word_list	*words;
	t_word_list	*prev;
	int			i;

	words = cmd->words;
	prev = NULL;
	while (words)
	{
		if (words->word.flags & W_GLOBEXP)
			if (!expand_glob_argv(words, words->word.word, &cmd->argc))
				return (FAILURE);
		if (words->word.flags & (W_HASHDOLLAR | W_EXITSTATUS))
		{
			words->word.word = expand_str(words->word.word, FALSE);
			words = expand_word_split(cmd, prev, words);
		}
		prev = words;
		words = words->next;
	}
	cmd->argv = xcalloc(sizeof(char *) * (cmd->argc + 1));
	words = cmd->words;
	i = -1;
	while (words)
	{
		cmd->argv[++i] = remove_quote(words->word.word);
		words->word.word = NULL;
		words = words->next;
	}
	return (SUCCESS);
}

int
	expand_command(t_command *cmd)
{
	if (!expand_argv(cmd))
		return (FAILURE);
	if (!expand_filename(cmd->redirects))
		return (FAILURE);
	return (SUCCESS);
}
