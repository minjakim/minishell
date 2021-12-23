/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:07:54 by snpark            #+#    #+#             */
/*   Updated: 2021/12/23 10:50:53 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	glob_compare(const char *pat, const char *str)
{
	while (*pat != '*' && *pat != '\0' && *str == '\0')
	{
		if (*pat != *str)
			return (*pat - *str);
		++pat;
		++str;
	}
	if (*pat == '*')
		return (0);
	return (*pat - *str);
}

int
	glob_strmatch(const char *pat, const char *str)
{
	int		skip;

	if ((*pat != '.' && *str == '.') || (*pat != '*' && glob_compare(pat, str)))
		return (FAILURE);
	skip = 0;
	while (*pat && *str)
	{
		if (*pat == '*' && *pat != '\0')
			++pat;
		if (*pat != '*' && glob_compare(pat, str))
			++str;
		else
			skip = 1;
		if (skip && *pat != '*' && *pat != '\0')
			++pat;
		if (skip && *str)
			++str;
		if (skip && *pat == '*')
			skip = 0;
		if (*pat == '/' && *(pat + 1) == '\0')
			++pat;
	}
	if (*pat == '\0' || (*pat == '*' && *(pat + 1) == '\0' && *str == '\0'))
		return (SUCCESS);
	return (FAILURE);
}

int
	glob_check_dir(const char *pat, const int type)
{
	while (*pat)
		pat++;
	if (*(pat - 1) == '/' && type & DT_DIR)
		return (TRUE);
	else if (*(pat - 1) == '/' && !(type & DT_DIR))
		return (FALSE);
	return (TRUE);
}

char
	*get_match_string(struct dirent *entry, const char *const pat)
{
	char	*offset;
	char	*dest;

	offset = ft_strchr(pat, '/');
	if (offset)
	{
		dest = xcalloc(sizeof(char) * (entry->d_namlen + 2));
		return (ft_strcat(ft_strcpy(dest, entry->d_name), "/"));
	}
	else
		return (ft_strdup(entry->d_name));
	return (NULL);
}
