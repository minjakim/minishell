/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:10:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/16 14:30:33 by snpark           ###   ########.fr       */
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
			t_redirect *new_unit)
{
	t_word_list	*temp;
	t_redirect	*handler;

	temp = words->next;
	free(words->word.word);
	free(words);
	if (new_unit->flags == 0)
		new_unit->here_doc_eof = words->word.word;
	else
		ft_memcpy(&new_unit->redirectee.filename, words->word.word, \
				sizeof(t_word_desc));
	words = temp->next;
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
	return (temp);
}

static t_word_list
	*attach_redirect(t_command *command, t_word_list *words)
{
	t_redirect	*new_unit;

	new_unit = xmalloc(sizeof(t_redirect));
	ft_memset(new_unit, 0, sizeof(t_redirect));
	if (words->word.flags & (W_LESS | W_LESS_LESS))
	{
		new_unit->redirector = STDIN_FILENO;
		command->flags |= CMD_STDIN_REDIR;
	}
	else if (words->word.flags & (W_GRATER | W_GRATER_GRATER))
	{
		new_unit->redirector = STDOUT_FILENO;
		command->flags |= CMD_STDOUT_REDIR;
	}
	if (words->word.flags & W_LESS)
		new_unit->flags = O_RDONLY;
	else if (words->word.flags & W_GRATER)
		new_unit->flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (words->word.flags & W_GRATER_GRATER)
		new_unit->flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		new_unit->flags = 0;
	return (attach_filename(command, words, new_unit));
}

static t_word_list
	*command_end(t_command **dest, t_command *command, t_word_list *words)
{
	t_command	*next_command;
	t_word_list	*temp;

	next_command = xmalloc(sizeof(t_command));
	command->next = next_command;
	command->connector = words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR);
	if (words->word.flags & W_PIPE)
	{
		command->flags |= CMD_PIPE | CMD_IGNORE_RETURN | CMD_NO_FORK;
		next_command->flags |= CMD_PIPE | CMD_NO_FORK;
	}
	temp = words->next;
	free(words->word.word);
	free(words);
	return (temp);
}

int
	command_handler(t_word_list *words, t_shell *mini)
{
	t_command	*command;

	command = xmalloc(sizeof(t_command));
	ft_memset(command, 0, sizeof(t_command));
	mini->command = command;
	while (words)
	{
		if (words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR))
			words = command_end(&command, command, words);
		else if (words->word.flags & W_REDIRECT)
			words = attach_redirect(command, words);
		else if (words->word.flags & W_ARG)
			words = attach_words(command, words);
		else
			words = words->next;
	}
	return (SUCCESS);
}
