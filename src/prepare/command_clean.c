/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:43:57 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/15 21:32:25 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_word_list
	*word_list_free(t_word_list *words)
{
	t_word_list	*tmp;

	while (words)
	{
		if (words->word.word)
			free(words->word.word);
		tmp = words;
		words = words->next;
		free(tmp);
	}
	return (NULL);
}

void
	command_clean(t_shell *mini)
{
	t_redirect	*rd_handler;
	void		*temp;
	int			i;

	while (mini->command)
	{
		word_list_free(mini->command->words);
		i = -1;
		if (mini->command->argv)
		{
			while (mini->command->argv[++i])
				free(mini->command->argv[i]);
			free(mini->command->argv);
		}
		rd_handler = mini->command->redirects;
		while (rd_handler)
		{
			if (rd_handler->flags == 0)
				free(rd_handler->here_doc_eof);
			else
				free(rd_handler->redirectee.filename.word);
			temp = rd_handler->next;
			free(rd_handler);
			rd_handler = temp;
		}
		if (mini->command->path)
			free(mini->command->path);
		free(mini->command);
		mini->command = temp;
	}
}
