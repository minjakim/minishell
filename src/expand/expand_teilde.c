/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_teilde.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:51:12 by snpark            #+#    #+#             */
/*   Updated: 2021/12/17 20:05:14 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * ~
 * =~ :~
 * ~+ ~-
 */

int
	is_teilde(const char *const str, int i, int quote)
{
	if (quote != 0 && \
			!(i == 0 || (i > 1 && (str[i - 1] == '=' || str[i - 1] == ':'))))
		return (0);
	if (str[i] == '~' && (str[i + 1] == '\0' || str[i + 1] == '/' ))
		return (1);
	if (str[i] == '~' && str[i + 2] == '+' && \
			(str[i + 2] == '\0' || str[i + 2] == '/' ))
		return (2);
	if (str[i] == '~' && str[i + 2] == '-' && \
			(str[i + 2] == '\0' || str[i + 2] == '/' ))
		return (3);
	return (0);
}

char
	*expand_teilde(char *filename, int i)
{
	char			*dirname;
	char			*dest;
	int				dest_len;
	const int		type = is_teilde(filename, i, 0);

	if (type == 1)
		dirname = getenv("HOME");
	else if (type == 2)
		dirname = getenv("PWD");
	else if (type == 3)
		dirname = getenv("OLDPWD");
	dest_len = ft_strlen(filename) + ft_strlen(dirname) + 1;
	dest = xcalloc(sizeof(char) * dest_len);
	if (type == 1)
		ft_strcat(ft_strcat(ft_strncpy(dest, filename, i), dirname), filename + i + 1);
	else
		ft_strcat(ft_strcat(ft_strncpy(dest, filename, i), dirname), filename + i + 2);
	free(filename);
	return (dest);
}
