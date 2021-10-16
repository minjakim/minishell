/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:03:49 by snpark            #+#    #+#             */
/*   Updated: 2021/10/16 13:36:51 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int
	cd(char **argv, char **envp)
{
	const char	*path = argv[1];
	int			ret;
	char		*tmp;

	(void)envp;
	if (path == NULL)
		ret = chdir(envp[ms_getenv("HOME", envp).key]);
	else
		ret = chdir(path);
	if (ret == -1)
	{
		//stderr bash: cd: argv[1]: strerror(errno)
		write(2, "bash: cd: ", 10);
		write(2, argv[1], strlen(argv[1]));
		write(2, ": ", 2);
		write(2, strerror(errno), strlen(strerror(errno)));
		//exit satus3
	}
	//check current wd
	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	free(tmp);
	return (1);
}
