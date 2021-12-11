/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_make.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:10:32 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 17:29:46 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_word_list
	*attach_words(t_command *cmd, t_word_list *words)
{
	t_word_list	*handler;
	t_word_list	*tmp;

	if (cmd->value.simple.words == NULL)
		cmd->value.simple.words = words;
	else
	{
		handler = cmd->value.simple.words;
		while (handler->next)
			handler = handler->next;
		handler->next = words;
	}
	tmp = words->next;
	words->next = NULL;
	return (tmp);
}

t_word_list
	*attach_redirect(t_command *cmd, t_word_list *words)
{
	t_redirect	*handler;
	t_redirect	*new_unit;
	t_word_list	*tmp;
	int			count;


	new_unit = malloc(sizeof(t_redirect));
	if (new_unit == NULL)
		return (NULL);//error
	ft_memset(new_unit, 0, sizeof(t_redirect));
	if (words->word.flags & (W_LESS | W_LESS_LESS))
	{
		new_unit->redirector = STDIN_FILENO;
		cmd->flags |= CMD_STDIN_REDIR;
	}
	else if (words->word.flags & (W_GRATER | W_GRATER_GRATER))
	{
		new_unit->redirector = STDOUT_FILENO;
		cmd->flags |= CMD_STDOUT_REDIR;
	}

	if (words->word.flags & W_LESS)
		new_unit->flags = O_RDONLY;
	else if (words->word.flags & W_GRATER)
		new_unit->flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (words->word.flags & W_GRATER_GRATER)
		new_unit->flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		new_unit->flags = 0;

	tmp = words;
	words = words->next;
	free(tmp->word.word);
	free(tmp);

	if (!(words->word.flags & W_FILENAME))
		return (NULL);//error
	if (new_unit->flags == 0)
		new_unit->here_doc_eof = words->word.word;
	else
	{
		new_unit->redirectee.filename.word = words->word.word;
		new_unit->redirectee.filename.flags |= words->word.flags;
	}

	tmp = words->next;
	free(words);

	if (cmd->value.simple.redirects == NULL)
		cmd->value.simple.redirects = new_unit;
	handler = cmd->value.simple.redirects;
	count = 0;
	while (handler->next && ++count <= 16)
		handler = handler->next;
	if (count > 16)
		return (NULL);//error 리다이렉트 수 제한 넘김
	handler->next = new_unit;
	return (tmp);
}

t_word_list
	*command_end(t_command **dest, t_command *cmd, t_word_list *words)
{
	t_command	*next_cmd;
	t_word_list	*tmp;

	cmd->type = cm_connection;
	next_cmd = malloc(sizeof(t_command));
	if (next_cmd == NULL)
		return (NULL);//error;
	cmd->value.connection.next = next_cmd;

	cmd->value.connection.connector = words->word.flags & (W_PIPE | W_AND_AND | W_OR_OR);

	if (words->word.flags & W_PIPE)
	{
		cmd->flags |= CMD_PIPE | CMD_IGNORE_RETURN | CMD_NO_FORK;
		next_cmd->flags |= CMD_PIPE | CMD_NO_FORK;
	}
	tmp = words->next;
	free(words->word.word);
	free(words);
	return (tmp);
}

int
	command_make(t_word_list *words, t_shell *mini)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (1);
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
	command->type = cm_simple;
	return (0);
}
