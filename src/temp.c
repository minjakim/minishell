/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:10:32 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/10 14:11:58 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	mini_null(t_shell *mini)
{
	(void)mini;
	return (0);
}

void
	tmp_print_list(t_word_list *tmp)
{
	while (tmp)
	{
		printf("%s %d\n", tmp->word.word, tmp->word.flags);
		tmp = tmp->next;
	}
}

