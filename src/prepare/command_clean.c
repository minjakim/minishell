/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:43:57 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/13 09:34:24 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	cmmand_clean(t_shell *mini)
{
	t_word_list *wl_handler;
	t_redirect	*rd_handler;
	void		*temp;
	int			i;

	while (mini->command)
	{
		wl_handler = mini->command->words;
		while (wl_handler)
		{
			temp = wl_handler->next;
			free(wl_handler);
			wl_handler = temp;
		}
		i = -1;
		if (mini->command->argv)
		{
			while (mini->command->argv[++i])
				free(mini->command->argv[i]);
			free(mini->command->argv);
		}
		rd_handler = mini->command->redirects;
		while (rd_handler)
		{
			if (rd_handler->flags == 0)
				free(rd_handler->here_doc_eof);
			else
				free(rd_handler->redirectee.filename.word);
			temp = rd_handler->next;
			free(rd_handler);
			rd_handler = temp;
		}
		if (mini->command->path)
			free(mini->command->path);
		free(mini->command);
		mini->command = temp;
	}
}
