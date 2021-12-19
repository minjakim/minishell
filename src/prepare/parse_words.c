/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:10:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/18 21:15:12 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_word_list
	*attach_words(t_command *command, t_word_list *words)
{
	t_word_list	*handler;
	t_word_list	*next_word;

	if (command->words == NULL)
		command->words = words;
	else
	{
		handler = command->words;
		while (handler->next)
			handler = handler->next;
		handler->next = words;
	}
	next_word = words->next;
	words->next = NULL;
	return (next_word);
}

static t_word_list
	*attach_filename(t_command *command, t_word_list *words, \
			t_redirect *new_unit, int flag)
{
	t_word_list	*temp;
	t_redirect	*handler;

	if (flag & W_LESS_LESS)
		new_unit->here_doc_eof = words->word.word;
	new_unit->redirectee.filename.word = words->word.word;
	new_unit->redirectee.filename.flags = words->word.flags;
	temp = words;
	words = words->next;
	free(temp);
	if (command->redirects == NULL)
		command->redirects = new_unit;
	else
	{
		handler = command->redirects;
		while (handler->next)
			handler = handler->next;
		handler->next = new_unit;
	}
	return (words);
}

static t_word_list
	*attach_redirect(t_command *command, t_word_list *words)
{
	t_redirect	*new_unit;
	t_word_list	*next_words;

	new_unit = xcalloc(sizeof(t_redirect));
	if (words->word.flags & (W_LESS | W_LESS_LESS))
	{
		new_unit->redirector = STDIN_FILENO;
		command->flags |= CMD_STDIN_REDIR;
		new_unit->flags = O_RDONLY;
	}
	else if (words->word.flags & (W_GRATER | W_GRATER_GRATER))
	{
		new_unit->redirector = STDOUT_FILENO;
		command->flags |= CMD_STDOUT_REDIR;
	}
	if (words->word.flags & W_GRATER)
		new_unit->flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (words->word.flags & W_GRATER_GRATER)
		new_unit->flags = O_WRONLY | O_CREAT | O_APPEND;
	next_words = attach_filename(command, words->next, new_unit, words->word.flags);
	xfree(words->word.word, words, NULL, NULL);
	return (next_words);
}

static t_word_list
	*end_of_block(t_command **command, t_word_list *words)
{
	t_command	*next_command;
	t_word_list	*temp_words;
	t_io		piped;

	next_command = xcalloc(sizeof(t_command));
	next_command->io.in = STDIN_FILENO;
	next_command->io.out = STDOUT_FILENO;
	(*command)->next = next_command;
	(*command)->connector = words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR);
	if (words->word.flags & W_PIPE)
	{
		pipe(piped.fd);
		(*command)->io.out = piped.in;
		next_command->io.in = piped.out;
		(*command)->flags |= CMD_SUBSHELL | CMD_PIPE | CMD_NO_FORK | CMD_IGNORE_RETURN;
		next_command->flags |= CMD_SUBSHELL | CMD_PIPE | CMD_NO_FORK;
	}
	(*command) = next_command;
	temp_words = words;
	words = words->next;
	xfree(temp_words->word.word, temp_words, NULL, NULL);
	return (words);
}

t_command
	*parse_words(t_word_list *words)
{
	t_command	*command;

	command = xcalloc(sizeof(t_command));
	command->io.in = STDIN_FILENO;
	command->io.out = STDOUT_FILENO;
	while (words)
	{
		if (words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR))
			words = end_of_block(&command, words);
		else if (words->word.flags & W_REDIRECT)
			words = attach_redirect(command, words);
		else if (words->word.flags & W_ARG)
			words = attach_words(command, words);
		else
			words = words->next;
	}
	return (command);
}
