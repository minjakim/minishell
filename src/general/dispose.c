/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:43:57 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/21 09:05:54 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	disposer(void *obj0, void *obj1, void *obj2, void *obj3)
{
	xfree(obj0);
	xfree(obj1);
	xfree(obj2);
	xfree(obj3);
}

void
	*dispose_words(t_word_list *words)
{
	t_word_list	*temp;

	while (words)
	{
		temp = words;
		words = words->next;
		disposer(temp->word.word, temp, NULL, NULL);
	}
	return (NULL);
}

void
	dispose_argv(char **argv)
{
	int	i;

	i = -1;
	if (argv)
	{
		while (argv[++i])
			free(argv[i]);
		free(argv);
	}
}

static void
	dispose_redirect(t_redirect *redirects)
{
	t_redirect	*temp;

	while (redirects)
	{
		temp = redirects;
		redirects = redirects->next;
		disposer(temp->redirectee.filename.word, temp, NULL, NULL);
	}
}

void
	dispose_cmd(t_command *cmd)
{
	t_command	*temp;
	int			i;

	while (cmd)
	{
		dispose_words(cmd->words);
		dispose_argv(cmd->argv);
		dispose_redirect(cmd->redirects);
		temp = cmd;
		cmd = cmd->next;
		disposer(temp->path, temp, NULL, NULL);
	}
}
