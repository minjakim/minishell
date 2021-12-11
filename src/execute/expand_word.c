/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:49:42 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 09:57:26 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int
	is_quote(const char c, int quote)
{
	return ((c == '\'' || c == '\"') && ((quote ^ c ) != 5));
}

int
	is_key(const char *str, const int i, const int quote)
{
	return ((quote == '\"' || quote == '\0') && str[i] == '$' && \
			legal_variable_starter(str[i + 1]));
}

static char
	*expand_env(char *src, int i, int flags)
{
	t_hash	hash;
	int		key_len;
	int		dest_len;
	char	*dest;

	key_len = 0;
	while (legal_variable_char(src[++key_len + i]))
		;
	hash.key = strndup(src + i + 1, key_len - 1);
	hash.value = getenv(hash.key);
	if (i == 0 && flags & W_FILENAME && (!hash.value || !*hash.value))
		return (NULL);//bash: argv[1]: ambiguas redirect
	dest_len = ft_strlen(src) - key_len + ft_strlen(hash.value);
	dest = malloc(sizeof(char) * dest_len);
	if (dest == NULL)
		return (NULL);
	ft_memset(dest, 0, sizeof(char) * dest_len);
	strcat(strcat(strncpy(dest, src, i), hash.value), src + i + key_len);
	free(hash.key);
	free(src);
	return (dest);
}

void
	remove_quote(char *str)
{
	int		quote;

	quote = 0;
	while (*str)
	{
		if (is_quote(*str, quote))
		{
			quote ^= *str;
			ft_strmove(str, str + 1, ft_strlen(str + 1));
		}
		else
			++str;
	}
}

int
	expand_word(t_word_desc *desc)
{
	char	*handle;
	int		quote;
	int		i;

	handle = desc->word;
	quote = 0;
	i = 0;
	while (handle[i])
	{
		if (is_key(handle, i, quote))
			handle = expand_env(handle, i, desc->flags);
		else if (is_teilde(handle, i, quote))
			handle = ft_teilde_expand(handle, i);
		if (handle == NULL)
			return (1);
		if (is_quote(handle[i], quote))
			quote ^= handle[i];
		++i;
	}
	return (0);
}
