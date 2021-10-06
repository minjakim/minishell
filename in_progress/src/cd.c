/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:03:49 by snpark            #+#    #+#             */
/*   Updated: 2021/10/06 17:08:12 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(char **argv, char **envp)
{
	const char *path = argv[1];
	int			ret;
	char		*tmp;

	(void)envp;
	if (path == NULL)
		ret = chdir(getenv("HOME"));
	else
		ret = chdir(path);
	if (ret == -1)
		;//errno에 따라 출력
	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp); 
	free(tmp);
	return (1);
}
