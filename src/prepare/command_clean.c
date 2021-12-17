/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:43:57 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/17 14:52:52 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_word_list
	*word_list_free(t_word_list *words)
{
	t_word_list	*next_word;

	while (words)
	{
		if (words->word.word)
			free(words->word.word);
		next_word = words->next;
		free(words);
		words = next_word;
	}
	return (NULL);
}

static void
	clean_argv(char **argv)
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
	clean_redirect(t_redirect *rd_handler)
{
	void		*next;

	while (rd_handler)
	{
		if (rd_handler->here_doc_eof)
			free(rd_handler->here_doc_eof);
		else
			free(rd_handler->redirectee.filename.word);
		next = rd_handler->next;
		free(rd_handler);
		rd_handler = next;
	}
}

void
	command_clean(t_shell *mini)
{
	void		*temp;
	int			i;

	while (mini->command)
	{
		word_list_free(mini->command->words);
		clean_argv(mini->command->argv);
		clean_redirect(mini->command->redirects);
		if (mini->command->path)
			free(mini->command->path);
		temp = mini->command->next;
		free(mini->command);
		mini->command = temp;
	}
	mini->command = NULL;
}
