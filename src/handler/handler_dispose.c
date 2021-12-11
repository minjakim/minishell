/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 08:02:58 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/11 09:58:33 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	clean_cmd(t_shell *mini)
{
	t_word_list *wl_handler;
	t_redirect	*rd_handler;
	void		*tmp;
	int			i;

	while (mini->command)
	{
		wl_handler = mini->command->value.simple.words;
		while (wl_handler)
		{
			tmp = wl_handler->next;
			free(wl_handler);
			wl_handler = tmp;
		}
		i = -1;
		if (mini->command->value.simple.argv)
		{
			while (mini->command->value.simple.argv[++i])
				free(mini->command->value.simple.argv[i]);
			free(mini->command->value.simple.argv);
		}
		rd_handler = mini->command->value.simple.redirects;
		while (rd_handler)
		{
			if (rd_handler->flags == 0)
				free(rd_handler->here_doc_eof);
			else
				free(rd_handler->redirectee.filename.word);
			tmp = rd_handler->next;
			free(rd_handler);
			rd_handler = tmp;
		}
		if (mini->command->value.simple.path)
			free(mini->command->value.simple.path);
		if (mini->command->type == cm_connection)
		{
			tmp = mini->command->value.connection.next;
			free(mini->command);
			mini->command = tmp;
		}
		if (mini->command->type == cm_simple)
		{
			free(mini->command);
			mini->command = NULL;
		}
	}
}
