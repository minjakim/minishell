/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:03:50 by snpark            #+#    #+#             */
/*   Updated: 2021/12/12 15:14:37 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int
	set_path(t_shell *mini, char *dirname, char *key)
{
	char		*assignment;
	const int	len = sizeof(char) * (ft_strlen(dirname) + ft_strlen(key) + 2);

	assignment = malloc(len);
	if (assignment == NULL)
		return (FAIL);
	ft_memset(assignment, 0, len);
	ft_strcat(ft_strcpy(assignment, key), dirname);
	if (assignment == NULL)
		return (FAIL);
	if (declare_add(&mini->env.declare, assignment, H_EXPORT) != 0)
		return (FAIL);
	free(assignment);
	return (SUCCESS);
}

static char
	*get_path(char **argv)
{
	char	*dirname;

	if (argv && argv[0] != NULL && argv[1] == NULL)
	{
		dirname = getenv("HOME");
		return (dirname);
	}
	else if (argv && argv[0] != NULL && ft_strcmp(argv[1], "-") == 0)
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
		dirname = get_path(mini->command->argv);
	if (dirname == NULL)
		return (1);
	if (chdir(dirname) == ERROR)
		return (1);
	if (!set_path(mini, oldpwd, "OLDPWD="))
		return (1);
	if (!set_path(mini, dirname, "PWD="))
		return (1);
	free(oldpwd);
	if (!envp_update(&mini->env, 1))
		return (1);
	return (0);
}
