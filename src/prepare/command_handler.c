/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:10:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/17 21:58:08 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	*attach_redirect(t_command *command, t_word_list *words)
{
	t_redirect	*new_unit;
	t_word_list	*next_word;

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
	next_word = attach_filename(command, words->next, new_unit, words->word.flags);
	free(words->word.word);
	free(words);
	return (next_word);
}

static t_word_list
	*command_end(t_command **command, t_word_list *words)
{
	t_command	*next_command;
	t_word_list	*temp;
	t_io		pipe_fd;

	next_command = xcalloc(sizeof(t_command));
	next_command->io.fd[0] = STDIN_FILENO;
	next_command->io.fd[1] = STDOUT_FILENO;
	(*command)->next = next_command;
	(*command)->connector = words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR);
	if (words->word.flags & W_PIPE)
	{
		pipe(pipe_fd.fd);
		(*command)->io.out = pipe_fd.in;
		next_command->io.in = pipe_fd.out;
		(*command)->flags |= CMD_PIPE | CMD_IGNORE_RETURN | CMD_NO_FORK;
		next_command->flags |= CMD_PIPE | CMD_NO_FORK;
	}
	(*command) = next_command;
	temp = words;
	words = words->next;
	free(temp->word.word);
	free(temp);
	return (words);
}

t_command
	*command_handler(t_word_list *words)
{
	t_command	*command;

	command = xcalloc(sizeof(t_command));
	command->io.fd[0] = STDIN_FILENO;
	command->io.fd[1] = STDOUT_FILENO;
	while (words)
	{
		if (words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR))
			words = command_end(&command, words);
		else if (words->word.flags & W_REDIRECT)
			words = attach_redirect(command, words);
		else if (words->word.flags & W_ARG)
			words = attach_words(command, words);
		else
			words = words->next;
	}
	return (command);
}
