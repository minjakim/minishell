/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 20:56:06 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 07:39:50 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	is_expand(int flags)
{
	return (flags & (W_HASHDOLLAR | W_QUOTED | W_DQUOTED | \
				W_TILDEEXP | W_HASHQUOTEDNULL));
}

//int glob_expand(t_word_list *list)
//{
//	char	*cwd;
//	t_word_desc	;
//	t_word_list	glob_expand_list;
//
//	cwd = getcwd(NULL, 0);
//
//	//glob expand?
//	//여러개의 인자가 생길 수 있기 때문에 따로 뺐다.
//	//리다이렉트의 경우 하나만 특정 가능하면 실행되는데
//	// 여러개 있으면 ambiguas redirect란 에러메시지가 출력 된다.
//	//일치하는게 없으면 그대로 놔둔다.
//}

static char
	**make_argv(t_word_list *list, int argc)
{
	char	**dest;
	int		i;

	dest = malloc(sizeof(char *) * (argc + 1));
	if (dest == NULL)
		return (NULL);
	memset(dest, 0, sizeof(char *) * (argc + 1));
	i = -1;
	while (list)
	{
		dest[++i] = strdup(list->word.word);//그냥 바로 집어넣을 수도 있음
		if (dest[i] == NULL)
			return (NULL);
		list = list->next;
	}
	return (dest);
}

static int
	expand_argv(t_command *cmd)
{
	t_word_list	*list;
	int			argc;
	int			i;

	while (cmd)
	{
		list = cmd->value.simple.words;
		argc = 0;
		while (list)
		{
			if (is_expand(list->word.flags))
				if (expand_word(&list->word) != 0)
					return (1);
//			if (list->word->flags & W_GLOBEXP)
//				glob_expand(list);
			remove_quote(list->word.word);
			list = list->next;
			++argc;
		}
		cmd->value.simple.argv = make_argv(cmd->value.simple.words, argc);
		if (cmd->value.simple.argv == NULL)
			return (1);
		if (cmd->type == cm_connection)
			cmd = cmd->value.connection.next;
		else if (cmd->type == cm_simple)
			return (0);
	}
	return (0);
}

static int
	expand_filename(t_redirect *redirects)
{
	while (redirects)
	{
		if (redirects->flags != 0 && is_expand(redirects->redirectee.filename.flags))
		{
			if (expand_word(&redirects->redirectee.filename) != 0)
				return (1);
//			if (glob_expand() != 0)
//				return (1);//argv[1]: ambiguas redirection
			remove_quote(redirects->redirectee.filename.word);
		}
		if (redirects->flags == 0 && redirects->redirectee.filename.flags & (W_QUOTED | W_DQUOTED))
			remove_quote(redirects->here_doc_eof);
		redirects = redirects->next;
	}
	return (0);
}

int
	expand_cmd(t_shell *mini)
{
	if (expand_argv(mini->cmd) != 0)
		return (1);
	if (expand_filename(mini->cmd->value.simple.redirects))
		return (1);
	return (0);
}
