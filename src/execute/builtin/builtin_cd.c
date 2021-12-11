/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:03:50 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 11:14:39 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int
	set_path(t_shell *mini, char *dirname, char *key)
{
	char			*assignment;
	const int		len = sizeof(char) * (strlen(dirname) + ft_strlen(key) + 2);

	assignment = malloc(len);
	if (assignment == NULL)
		return (1);
	ft_memset(assignment, 0, len);
	strcat(strcpy(assignment, key), dirname);
	if (assignment == NULL)
		return (1);
	if (declare_add(&mini->env.declare, assignment, H_EXPORT) != 0)
		return (1);
	free(assignment);
	return (0);
}

static char
	*builtin_cd_getpath(char **argv)
{
	char	*dirname;

	if (argv && argv[0] != NULL && argv[1] == NULL)
	{
		dirname = getenv("HOME");
		return (dirname);
	}
	else if (argv && argv[0] != NULL && strcmp(argv[1], "-") == 0)
	{
		dirname = getenv("OLDPWD");
		return (dirname);
	}
	else
		return (argv[1]);
	return (NULL);
}
/*getenv("HOME") == NULL
 * error msg "HOME not set"
 * getenv("OLDPWD") == NULL
 * error msg "OLDPWD not set"*/

int
	builtin_cd(t_shell *mini)
{
	char	*dirname;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (1);
	if (mini && mini->command)
		dirname = builtin_cd_getpath(mini->command->value.simple.argv);
	if (dirname == NULL)
		return (1);
	if (chdir(dirname) == ERROR)
		return (1);
	if (set_path(mini, oldpwd, "OLDPWD=") != 0)
		return (1);
	if (set_path(mini, dirname, "PWD=") != 0)
		return (1);
	free(oldpwd);
	if (replace_envp(&mini->env, 1) != 0)
		return (1);
	return (0);
}
