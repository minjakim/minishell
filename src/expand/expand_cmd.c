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

static int
	is_expand(int flags)
{
	return (flags & (W_HASHDOLLAR | W_EXITSTATUS | W_GLOBEXP | W_ITILDE));
}

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
	expand_filename(t_redirect *redirects)
{
	char	*filename;
	int		flags;

	while (redirects)
	{
		filename = ft_strdup(redirects->redirectee.filename.word);
		flags = redirects->redirectee.filename.flags;
		if ((flags & (W_HASHDOLLAR | W_EXITSTATUS)) && \
				!(flags & W_NOEXPAND))
		{
			filename = expand_str(filename, FALSE);
			if (!filename || !*filename)
			{
				report_exception(NULL, redirects->redirectee.filename.word, \
						EX_AMBIGUAS, GENERAL_ERROR);
				return (FAILURE);
			}
			free(redirects->redirectee.filename.word);
			redirects->redirectee.filename.word = filename;
		}
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

	cmd->argv = xcalloc(sizeof(char *) * (cmd->argc + 1));
	list = cmd->words;
	i = -1;
	while (list)
	{
		if (list->word.flags & (W_HASHDOLLAR | W_EXITSTATUS))
			cmd->argv[++i] = expand_str(list->word.word, FALSE);
		else
			cmd->argv[++i] = list->word.word;
		list->word.word = NULL;
		remove_quote(cmd->argv[i]);
		list = list->next;
	}
	return (SUCCESS);
}

/* 여기에서 확장과 argv 완성 ~  조금 더 윗단(word 완성하는 단계)에서부터
argc가 채워져서 내려 오면 좋을 것 같음~*/

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
