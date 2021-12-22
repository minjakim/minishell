/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:17:59 by snpark            #+#    #+#             */
/*   Updated: 2021/12/19 23:16:28 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	flag_qoute_expand(t_word_list *words, const char *str)
{
	int	quote;

	quote = 0;
	if (!words->word.flags)
		words->word.flags |= W_ARG;
	while (*str)
	{
		if (is_quote(*str, quote))
			quote ^= *str;
		if (*str == '\'' && quote == '\'')
			words->word.flags |= W_QUOTED;
		if (*str == '\"' && quote == '\"')
			words->word.flags |= W_DQUOTED;
		if (quote != '\'' && *str == '$' && legal_variable_starter(*(str + 1)))
			words->word.flags |= W_HASHDOLLAR;
		if (quote != '\'' && *str == '$' && *(str + 1) == '?')
			words->word.flags |= W_EXITSTATUS;
		if (quote == 0 && *str == '*')
			words->word.flags |= W_GLOBEXP;
		if (quote == 0 && *str == '~')
			words->word.flags |= W_ITILDE;
		++str;
	}
	return (words->word.flags);
}

static int
	flag_connector(t_word_list *words, const char *const str, int old_flags)
{
	if (str[0] == '|' && str[1] == '|')
		words->word.flags |= W_OR_OR;
	else if (str[0] == '&' && str[1] == '&')
		words->word.flags |= W_AND_AND;
	else if (str[0] == '|')
		words->word.flags |= W_PIPE;
	else
		return (W_NOFLAG);
	if (!old_flags || old_flags & (W_AND_AND | W_PIPE | W_OR_OR))
		return (report_error_syntax(str));
	return (words->word.flags);
}

static int
	flag_redirect(t_word_list *words, const char *const str, int old_flags)
{
	if (str[0] != '>' && str[0] != '<')
		return (W_NOFLAG);
	if (old_flags & W_REDIRECT)
		return (report_error_syntax(str));
	if (str[0] == '<' && str[1] == '<')
		words->word.flags |= W_LESS_LESS;
	else if (str[0] == '<')
		words->word.flags |= W_LESS;
	else if (str[0] == '>' && str[1] == '>')
		words->word.flags |= W_GRATER_GRATER;
	else if (str[0] == '>')
		words->word.flags |= W_GRATER;
	if (words->next == NULL)
		return (report_error_syntax("newline"));
	if (words->word.flags & W_LESS_LESS && ++g_status.state.need_heredoc)
		words->next->word.flags |= (W_HEREDOC | W_NOEXPAND);
	else
		words->next->word.flags |= W_FILENAME;
	words->word.flags |= W_REDIRECT;
	return (words->word.flags);
}

int
	make_words(t_word_list *words)
{
	int	old_flags;

	old_flags = 0;
	while (words)
	{
		if (flag_redirect(words, words->word.word, old_flags) == EXCEPTION)
			return (EXCEPTION);
		if (g_status.state.need_heredoc >= HEREDOC_MAX)
			return (report_exception_fatal(EX_HEREDOC_MAX, ES_BADUSAGE));
		if (flag_connector(words, words->word.word, old_flags) == EXCEPTION)
			return (EXCEPTION);
		if (flag_qoute_expand(words, words->word.word) == EXCEPTION)
			return (EXCEPTION);
		old_flags = words->word.flags;
		if (!words->next && (old_flags & (W_AND_AND | W_OR_OR | W_PIPE)))
			return (report_error_syntax(words->word.word));
		words = words->next;
	}
	g_status.state.need_heredoc = 0;
	return (SUCCESS);
}
