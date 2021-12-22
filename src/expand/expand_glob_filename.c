/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob_filename.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:06:53 by snpark            #+#    #+#             */
/*   Updated: 2021/12/22 16:19:18 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char
	*expand_glob_find_one(DIR *dirinfo, char *pattern)
{
	struct dirent	*entry;
	char			*dest;

	dest = NULL;
	while (LOOP)
	{
		entry = readdir(dirinfo);
		if (entry == NULL)
			break ;
		if (glob_strmatch(pattern, entry->d_name) && \
				glob_check_dir(pattern, entry->d_type))
		{
			if (dest)
			{
				disposer(dest, pattern, NULL, NULL);
				return (NULL);
			}
			dest = get_match_string(entry, pattern);
		}
	}
	if (dest == NULL)
		dest = pattern;
	xfree(pattern);
	return (dest);
}

char
	*expand_glob_filename(char *pattern)
{
	char		*path;
	DIR			*dirinfo;
	char		*filename;

	path = ft_strchr(pattern, '/');
	if (path != NULL && path[1] != '\0')
		return (pattern);
	dirinfo = opendir(".");
	if (dirinfo == NULL)
	{
		report_error(NULL, NULL, errno);
		return (pattern);
	}
	filename = expand_glob_find_one(dirinfo, pattern);
	closedir(dirinfo);
	return (filename);
}
