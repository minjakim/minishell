/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:56:06 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 10:41:25 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//int expand_glob(t_word_list *list)
//{
//	char	*cwd;
//	t_word_desc	;
//	t_word_list	expand_glob_list;
//
//	cwd = getcwd(NULL, 0);
//
//	//glob expand?
//	//여러개의 인자가 생길 수 있기 때문에 따로 뺐다.
//	//리다이렉트의 경우 하나만 특정 가능하면 실행되는데
//	// 여러개 있으면 ambiguas redirect란 에러메시지가 출력 된다.
//	//일치하는게 없으면 그대로 놔둔다.
//}

static int
	is_expand(int flags)
{
	return (flags & (W_HASHDOLLAR | W_QUOTED | W_DQUOTED | \
				W_TILDEEXP | W_HASHQUOTEDNULL));
}

void
	remove_quote(char *str)
{
	int		quote;

	quote = 0;
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
}

static int
	expand_filename(t_redirect *redirects)
{
	while (redirects)
	{
		if (!redirects->here_doc_eof && is_expand(redirects->redirectee.filename.flags))
		{
			if (!expand_word(&redirects->redirectee.filename))
				return (FAILURE);
//			if (expand_glob() != 0)
//				return (FAILURE);//argv[1]: ambiguas redirection
			remove_quote(redirects->redirectee.filename.word);
		}
		redirects = redirects->next;
	}
	return (SUCCESS);
}

static int
	expand_argv(t_command *cmd)
{
	t_word_list	*list;
	int			i;

	while (cmd)
	{
		list = cmd->words;
		while (list)
		{
//			if (is_expand(list->word.flags))
//				if (!expand_word(&list->word))
//					return (FALSE);
////			if (list->word->flags & W_GLOBEXP)
////				expand_glob(list);
//			remove_quote(list->word.word);
			list = list->next;
			++cmd->argc;
		}
		cmd = cmd->next;
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

	if (!expand_argv(cmd))
		return (FAILURE);
	if (!expand_filename(cmd->redirects))
		return (FAILURE);
	cmd->argv = xcalloc(sizeof(char *) * (cmd->argc + 1));
	words = cmd->words;
	i = -1;
	while (words)
	{
		cmd->argv[++i] = words->word.word;
		words->word.word = NULL;
		words = words->next;
	}
	return (SUCCESS);
}
