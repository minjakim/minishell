/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:56:06 by snpark            #+#    #+#             */
/*   Updated: 2021/12/21 10:05:02 by snpark           ###   ########.fr       */
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

int
	is_ambiguas(char *filename, t_redirect *redirects)
{
	if (!filename || !*filename)
	{
		report_exception(NULL, redirects->redirectee.filename.word, \
				EX_AMBIGUAS, GENERAL_ERROR);
		if (!*filename)
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
			filename = expand_str(ft_strdup(filename), FALSE);
		if (!is_ambiguas(filename, redirects))
			return (FAILURE);
//		if ((flags & W_GLOBEXP) && !(flags & W_NOEXPAND))
		//	expand_glob(NULL, filename, NULL);
		remove_quote(redirects->redirectee.filename.word);
		redirects = redirects->next;
	}
	return (SUCCESS);
}

static int
	expand_argv(t_command *cmd)
{
	t_word_list	*list;
	int			i;

	list = cmd->words;
	while (list)
	{
		if (list->word.flags & (W_HASHDOLLAR | W_EXITSTATUS))
			list->word.word = expand_str(list->word.word, FALSE);
		if (list->word.flags & W_GLOBEXP)
			if (!expand_glob(list, list->word.word, &cmd->argc))
				return (FAILURE);
		list = list->next;
	}
	cmd->argv = xcalloc(sizeof(char *) * (cmd->argc + 1));
	list = cmd->words;
	i = -1;
	while (++i < cmd->argc)
	{
		cmd->argv[i] = remove_quote(list->word.word);
		list->word.word = NULL;
		list = list->next;
	}
	return (SUCCESS);
}

int
	expand_command(t_command *cmd)
{
	t_word_list	*words;
	int			i;

	while (cmd)
	{
		if (!expand_argv(cmd))
			return (FAILURE);
		if (!expand_filename(cmd->redirects))
			return (FAILURE);
		cmd = cmd->next;
	}
	return (SUCCESS);
}
