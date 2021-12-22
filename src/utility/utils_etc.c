/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_etc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:10:32 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/22 17:32:03 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	temp_print_list(t_word_list *temp)
{
	while (temp)
	{
		printf("%s %d\n", temp->word.word, temp->word.flags);
		temp = temp->next;
	}
}

void
	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*var_b;
	unsigned char	var_c;

	var_b = b;
	var_c = c;
	while (len--)
		*var_b++ = var_c;
	return (b);
}

