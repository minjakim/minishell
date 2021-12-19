/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:43:57 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/18 20:27:19 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_word_list
	*word_list_free(t_word_list *words)
{
	t_word_list	*temp;

	while (words)
	{
		if (words->word.word)
			free(words->word.word);
		temp = words;
		words = words->next;
		free(temp);
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
	void		*temp;

	while (rd_handler)
	{
		if (rd_handler->here_doc_eof)
			free(rd_handler->here_doc_eof);
		else
			free(rd_handler->redirectee.filename.word);
		temp = rd_handler;
		rd_handler = rd_handler->next;
		free(temp);
	}
}

void
	dispose(t_command *command)
{
	void	*temp;
	int		i;

	while (command)
	{
		word_list_free(command->words);
		clean_argv(command->argv);
		clean_redirect(command->redirects);
		if (command->path)
			free(command->path);
		temp = command;
		command = command->next;
		free(temp);
	}
}
