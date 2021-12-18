/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:10:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/18 14:10:49 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_word_list
	*attach_words(t_command *cmd, t_word_list *words)
{
	t_word_list	*handler;
	t_word_list	*next_word;

	if (cmd->words == NULL)
		cmd->words = words;
	else
	{
		handler = cmd->words;
		while (handler->next)
			handler = handler->next;
		handler->next = words;
	}
	next_word = words->next;
	words->next = NULL;
	return (next_word);
}

static t_word_list
	*attach_filename(t_command *cmd, t_word_list *words, \
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
	if (cmd->redirects == NULL)
		cmd->redirects = new_unit;
	else
	{
		handler = cmd->redirects;
		while (handler->next)
			handler = handler->next;
		handler->next = new_unit;
	}
	return (words);
}

static t_word_list
	*attach_redirect(t_command *cmd, t_word_list *words)
{
	t_redirect	*new_unit;
	t_word_list	*next_words;

	new_unit = xcalloc(sizeof(t_redirect));
	if (words->word.flags & (W_LESS | W_LESS_LESS))
	{
		new_unit->redirector = STDIN_FILENO;
		cmd->flags |= CMD_STDIN_REDIR;
		new_unit->flags = O_RDONLY;
	}
	else if (words->word.flags & (W_GRATER | W_GRATER_GRATER))
	{
		new_unit->redirector = STDOUT_FILENO;
		cmd->flags |= CMD_STDOUT_REDIR;
	}
	if (words->word.flags & W_GRATER)
		new_unit->flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (words->word.flags & W_GRATER_GRATER)
		new_unit->flags = O_WRONLY | O_CREAT | O_APPEND;
	next_words = attach_filename(cmd, words->next, new_unit, words->word.flags);
	xfree(words->word.word, words, NULL, NULL);
	return (next_words);
}

static t_word_list
	*cmd_end(t_command **cmd, t_word_list *words)
{
	t_command	*next_cmd;
	t_word_list	*temp_words;
	t_io		piped;

	next_cmd = xcalloc(sizeof(t_command));
	next_cmd->io.in = STDIN_FILENO;
	next_cmd->io.out = STDOUT_FILENO;
	(*cmd)->next = next_cmd;
	(*cmd)->connector = words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR);
	if (words->word.flags & W_PIPE)
	{
		pipe(piped.fd);
		(*cmd)->io.out = piped.in;
		next_cmd->io.in = piped.out;
		(*cmd)->flags |= CMD_PIPE | CMD_IGNORE_RETURN | CMD_NO_FORK;
		next_cmd->flags |= CMD_PIPE | CMD_NO_FORK;
	}
	(*cmd) = next_cmd;
	temp_words = words;
	words = words->next;
	xfree(temp_words->word.word, temp_words, NULL, NULL);
	return (words);
}

t_command
	*make_cmd(t_word_list *words)
{
	t_command	*cmd;

	cmd = xcalloc(sizeof(t_command));
	cmd->io.in = STDIN_FILENO;
	cmd->io.out = STDOUT_FILENO;
	while (words)
	{
		if (words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR))
			words = cmd_end(&cmd, words);
		else if (words->word.flags & W_REDIRECT)
			words = attach_redirect(cmd, words);
		else if (words->word.flags & W_ARG)
			words = attach_words(cmd, words);
		else
			words = words->next;
	}
	return (cmd);
}
