/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:10:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/13 13:54:24 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_word_list
	*attach_words(t_command *command, t_word_list *words)
{
	t_word_list	*handler;
	t_word_list	*temp;

	if (command->words == NULL)
		command->words = words;
	else
	{
		handler = command->words;
		while (handler->next)
			handler = handler->next;
		handler->next = words;
	}
	temp = words->next;
	words->next = NULL;
	return (temp);
}

t_word_list
	*attach_redirect(t_command *command, t_word_list *words)
{
	t_redirect	*handler;
	t_redirect	*new_unit;
	t_word_list	*temp;
	int			count;


	new_unit = malloc(sizeof(t_redirect));
	if (new_unit == NULL)
		return (NULL);//error
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

	temp = words;
	words = words->next;
	free(temp->word.word);
	free(temp);

	if (!(words->word.flags & W_FILENAME))
		return (NULL);//error
	if (new_unit->flags == 0)
		new_unit->here_doc_eof = words->word.word;
	else
	{
		new_unit->redirectee.filename.word = words->word.word;
		new_unit->redirectee.filename.flags |= words->word.flags;
	}

	temp = words->next;
	free(words);

	if (command->redirects == NULL)
		command->redirects = new_unit;
	handler = command->redirects;
	count = 0;
	while (handler->next && ++count <= 16)
		handler = handler->next;
	if (count > 16)
		return (NULL);
	handler->next = new_unit;
	return (temp);
}

t_word_list
	*command_end(t_command **dest, t_command *command, t_word_list *words)
{
	t_command	*next_command;
	t_word_list	*temp;

	next_command = malloc(sizeof(t_command));
	if (next_command == NULL)
		return (NULL);//error;
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
	command_make(t_word_list *words, t_shell *mini)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (FAILURE);
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
	return (0);
}
