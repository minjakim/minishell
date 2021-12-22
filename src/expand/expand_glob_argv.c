/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:11:42 by snpark            #+#    #+#             */
/*   Updated: 2021/12/22 16:24:22 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_word_list
	*glob_attach_list(t_word_list *words, char *pattern, \
			struct dirent *entry, int count)
{
	if (count == 0)
	{
		words->word.word = get_match_string(entry, pattern);
		words->next = NULL;
		words->word.flags &= ~W_GLOBEXP;
	}
	else
	{
		words->next = xcalloc(sizeof(t_word_list));
		words->next->word.word = get_match_string(entry, pattern);
		words->next->word.flags = words->word.flags;
		words = words->next;
	}
	return (words);
}

static int
	expand_glob_find_all(DIR *dirinfo, t_word_list *words, \
			char *pattern, int *argc)
{
	t_word_list		*temp;
	struct dirent	*entry;
	int				count;

	temp = words->next;
	count = -1;
	while (LOOP)
	{
		entry = readdir(dirinfo);
		if (entry == NULL)
			break ;
		if (glob_strmatch(pattern, entry->d_name) && glob_check_dir(pattern, \
					entry->d_type))
		{
			++count;
			words = glob_attach_list(words, pattern, entry, count);
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
	expand_glob_argv(t_word_list *words, char *pattern, int *argc)
{
	char			*path;
	DIR				*dirinfo;

	path = ft_strchr(pattern, '/');
	if (path != NULL && path[1] != '\0')
		return (SUCCESS);
	dirinfo = opendir(".");
	if (dirinfo == NULL)
	{
		report_error(NULL, NULL, errno);
		return (FAILURE);
	}
	expand_glob_find_all(dirinfo, words, pattern, argc);
	closedir(dirinfo);
	return (SUCCESS);
}
