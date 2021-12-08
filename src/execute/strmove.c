/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:23:21 by snpark            #+#    #+#             */
/*   Updated: 2021/12/06 19:23:32 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void
	strmove(char *dest, char *src, int len)
{
	if (len < 0)
		return ;
	while(len--)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = *src;
}

