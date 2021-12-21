/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:07:54 by snpark            #+#    #+#             */
/*   Updated: 2021/12/14 11:09:21 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	glob_compare(char *pat, char *str)
{
	while (*pat != '*' && *pat != '\0' && *str == '\0')
		if (*pat != *str)
			return (*pat - *str);
	return (*pat - *str);
}

static int
	strmatch(char *pat, char *str)
{
	int		i;
	int		skip;

	if (*pat != '.' && *str == '.')
		return (FAILURE);
	i = 0;
	skip = 0;
	while (*str)
	{
		if (pat[i] == '*' && pat[i] != '\0')
			i++;
		if (pat[i] != '*' && glob_compare(pat + i, str))
			++str;
		else
			skip = TRUE;
		if (skip && pat[i] != '*' && pat[i] != '\0')
			i++;
		if (skip && pat[i] == '*')
			skip = FALSE;
	}
	if (*pat)
		return (FAILURE);
	return (SUCCESS);
}

int
	expand_glob_word_list(DIR *dirinfo, t_word_list *words, char *pattern , int *argc)
{
	t_word_list		*temp;
	struct dirent	*entry;
	int		count;

	temp = words->next;
	count = -1;
	while (LOOP)
	{
		entry = readdir(dirinfo);
		if (entry == NULL)
			break ;
		if (strmatch(pattern, entry->d_name))
		{
			++count;
			words->word.word = ft_strdup(entry->d_name);
			words->next = xcalloc(sizeof(t_word_list));
			words->next->word.flags = words->word.flags & ~W_GLOBEXP;
			words = words->next;
		}
	}
	if (count > -1)
	{
	 	xfree(pattern);
		words->next = temp;
		*argc += count;
	}
	return (SUCCESS);
}

int
 	expand_glob(t_word_list *words, char *pattern, int *argc)
{
	char			*path;
	DIR				*dirinfo;
	struct dirent	*entry;
	t_word_list		*temp;

	printf("this is glob exp\n");
	path = ft_strchr(pattern, '/');
	if (path != NULL && path[1] != '\0')
		return (SUCCESS);
	dirinfo = opendir(".");
	if (dirinfo == NULL)
	{
		report_error(NULL, NULL, errno);
		return (FAILURE);
	}
	if (words)
		if (!expand_glob_word_list(dirinfo, words, pattern, argc))
			return (FAILURE);
	closedir(dirinfo);
	return (SUCCESS);
}
