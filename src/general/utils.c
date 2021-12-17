/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:07:20 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/17 19:43:25 by minjakim         ###   ########.fr       */
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

T_PTR
	xcalloc(size_t bytes)
{
	T_PTR	temp;

	temp = xmalloc(bytes);
	ft_memset(temp, 0, bytes);
	return (temp);
}
