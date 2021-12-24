/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:49:42 by snpark            #+#    #+#             */
/*   Updated: 2021/12/22 21:24:01 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	is_quote(const char c, int quote)
{
	return ((c == '\'' || c == '\"') && ((quote ^ c) != 5));
}

static int
	is_dollar(const char *str, const int i, const int quote)
{
	return ((quote == '\"' || quote == '\0') && str[i] == '$');
}

static char
	*expand_hashdollar(char *src, int i)
{
	char		*value;
	char		*key;
	char		*dest;
	int			key_len;

	key_len = 1;
	while (legal_variable_char(src[key_len + i]))
		++key_len;
	key = ft_strndup(src + i + 1, key_len - 1);
	value = declare_get_value(key);
	dest = xcalloc(sizeof(char) * \
			(ft_strlen(src) - key_len + ft_strlen(value) + 1));
	ft_strcat(ft_strcat(ft_strncpy(dest, src, i), value), \
			src + i + key_len);
	disposer(key, src, NULL, NULL);
	return (dest);
}

static char
	*expand_exitstatus(char *src, int i)
{
	char	exit_str[4];
	char	*dest;
	int		exit_status;
	int		exit_idx;

	exit_status = g_status.exit;
	exit_str[3] = '\0';
	exit_idx = 2;
	while (exit_idx >= 0)
	{
		exit_str[exit_idx] = '0' + (exit_status % 10);
		exit_status /= 10;
		if (!exit_status)
			break ;
		exit_idx--;
	}
	dest = xcalloc(sizeof(char) * (ft_strlen(src) - 1 + ft_strlen(exit_str)));
	ft_strcat(ft_strcat(ft_strncpy(dest, src, i), \
				exit_str + exit_idx), src + i + 2);
	xfree(src);
	return (dest);
}

char
	*expand_str(char *str, int heredoc)
{
	int		quote;
	int		i;

	quote = 0;
	i = -1;
	while (str[++i])
	{
		if (is_dollar(str, i, quote) && legal_variable_starter(str[i + 1]))
			str = expand_hashdollar(str, i);
		else if (is_dollar(str, i, quote) && str[i + 1] == '?')
			str = expand_exitstatus(str, i);
		if (!heredoc && is_quote(str[i], quote))
			quote ^= str[i];
	}
	return (str);
}
