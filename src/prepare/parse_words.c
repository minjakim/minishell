/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:10:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 12:23:31 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_word_list
	*attach_words(t_command *cmd, t_word_list *words)
{
	t_word_list	*next_word;
	t_word_list	*handler;

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
			t_redirect *redirect, int flag)
{
	t_redirect	*redirects;
	void		*temp;

	if (flag & W_LESS_LESS)
		redirect->heredoc_eof = words->word.word;
	redirect->redirectee.filename.word = words->word.word;
	words->word.word = NULL;
	redirect->redirectee.filename.flags = words->word.flags;
	temp = words;
	words = words->next;
	free(temp);
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
	next_words = attach_filename(cmd, words->next, redirect, words->word.flags);
	disposer(words->word.word, words, NULL, NULL);
	return (next_words);
}

static t_word_list
	*end_of_block(t_command *cmd, t_word_list *words)
{
	const int	devNull = open("/dev/null", O_WRONLY);
	t_word_list	*temp_words;
	t_io		piped;

	cmd->next = xcalloc_t_command();
	cmd->connector = words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR);
	if ((words->word.flags & W_PIPE) && (xpipe(piped.fd, NULL) != ERROR))
	{
		cmd->io.out = piped.in;
		cmd->next->io.in = piped.out;
		cmd->flags |= CMD_PIPE | CMD_IGNORE_RETURN;
		cmd->next->flags |= CMD_PIPE;
	}
	temp_words = words;
	words = words->next;
	disposer(temp_words->word.word, temp_words, NULL, NULL);
	return (words);
}

t_command
	*parse_words(t_word_list *words)
{
	t_command	*cmd;

	cmd = xcalloc_t_command();
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
	return (cmd);
}
