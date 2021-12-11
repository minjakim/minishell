/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:07:54 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 16:20:48 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	strmatch(char *pat, char *str, int flag)
{
	while(*pat && *str)
	{
		if (*pat == '*')
		{
			str++;
			if (*(pat + 1) == *str)
				pat++;
		}
		if (*pat != '*' && *pat == *str)
		{
			str++;
			pat++;
		}
		if (flag && *pat == '/' && *(pat + 1) == '\0' && *str == '\0')
			pat++;
		if (*pat != '*' && *pat != *str)
			return (0);
	}
	return (1);
}

char
 	**expand_glob(t_word_desc *word)
{
	char 	*filename;
	char	*slash;
	DIR		*dirinfo;
	struct dirent	*entry;
	int		is_dir;


	//filename = word->word;
	filename = "hello";
	slash = ft_strchr(filename, '/');
	if (slash != NULL && slash[1] != '\0')
		return (0);
	is_dir = (slash != NULL);
//	if ()
	dirinfo = opendir(".");
	if (dirinfo == NULL)
		return (NULL);//opendir err
	while (1)
	{
		entry = readdir(dirinfo);
		if (entry == NULL)
			break ;
		printf("%d %d ", is_dir, entry->d_type & DT_DIR);
		if (strmatch("*/", entry->d_name, (is_dir && entry->d_type & DT_DIR)))
			printf("match %s\n", entry->d_name);
		else
			printf("no match %s\n", entry->d_name);
//		if (entry->d_type == D_DIR && is_dir)
//		{
//		}
	}
	closedir(dirinfo);
	return (NULL);
}
