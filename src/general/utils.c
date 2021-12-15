/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:07:20 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/15 17:58:38 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

T_PTR
	xmalloc(size_t bytes)
{
	T_PTR	temp;

	temp = malloc(bytes);
	if (!temp)
		exception_error_fatal(errno);
	return (temp);
}
