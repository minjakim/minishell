/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:10:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 16:08:21 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_word_list
	*attach_words(t_command *cmd, t_word_list *words)
{
	t_word_list	*prev;
	t_word_list	*next;

	if (cmd->words == NULL)
		cmd->words = words;
	else
	{
		prev = cmd->words;
		while (prev->next)
			prev = prev->next;
		prev->next = words;
	}
	next = words->next;
	words->next = NULL;
	++cmd->argc;
	return (next);
}

static t_word_list
	*attach_filename(t_command *cmd, t_word_list *words, \
			t_redirect *redirect)
{
	t_redirect	*redirects;
	void		*temp;

	redirect->redirectee.filename.word = words->word.word;
	words->word.word = NULL;
	redirect->redirectee.filename.flags = words->word.flags;
	temp = words;
	words = words->next;
	xfree(temp);
	if (cmd->redirects == NULL)
		cmd->redirects = redirect;
	else
	{
		redirects = cmd->redirects;
		while (redirects->next)
			redirects = redirects->next;
		redirects->next = redirect;
	}
	return (words);
}

static t_word_list
	*attach_redirect(t_command *cmd, t_word_list *words)
{
	t_redirect	*redirect;
	t_word_list	*next_words;

	redirect = xcalloc(sizeof(t_redirect));
	if (words->word.flags & (W_LESS | W_LESS_LESS))
	{
		redirect->redirector = STDIN_FILENO;
		cmd->flags |= CMD_STDIN_REDIR;
		redirect->flags = O_RDONLY;
	}
	else if (words->word.flags & (W_GRATER | W_GRATER_GRATER))
	{
		redirect->redirector = STDOUT_FILENO;
		cmd->flags |= CMD_STDOUT_REDIR;
	}
	if (words->word.flags & W_GRATER)
		redirect->flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (words->word.flags & W_GRATER_GRATER)
		redirect->flags = O_WRONLY | O_CREAT | O_APPEND;
	next_words = attach_filename(cmd, words->next, redirect);
	disposer(words->word.word, words, NULL, NULL);
	return (next_words);
}

static t_word_list
	*end_of_block(t_command *cmd, t_word_list *words)
{
	const int	devNull = open("/dev/null", O_WRONLY);
	t_word_list	*temp;
	t_io		piped;

	cmd->next = xcalloc_t_command();
	cmd->connector = words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR);
	if ((words->word.flags & W_PIPE) && (xpipe(piped.fd, NULL) != ERROR))
	{
		cmd->io.out = piped.out;
		cmd->next->io.in = piped.in;
		cmd->flags |= CMD_PIPE | CMD_IGNORE_RETURN;
		cmd->next->flags |= CMD_PIPE;
	}
	temp = words;
	words = words->next;
	disposer(temp->word.word, temp, NULL, NULL);
	return (words);
}

t_command
	*parse_words(t_word_list *words)
{
	t_command *const	head = xcalloc_t_command();
	t_command			*cmd;

	cmd = head;
	while (words)
	{
		if (words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR))
		{
			words = end_of_block(cmd, words);
			cmd = cmd->next;
		}
		else if (words->word.flags & W_REDIRECT)
			words = attach_redirect(cmd, words);
		else if (words->word.flags & W_ARG)
			words = attach_words(cmd, words);
		else
			words = words->next;
	}
	return (head);
}
