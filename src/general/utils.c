/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:07:20 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/18 23:26:11 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

T_PTR
	xmalloc(size_t bytes)
{
	T_PTR	temp;

	temp = malloc(bytes);
	if (!temp)
		report_error_fatal(errno);
	return (temp);
}

T_PTR
	xcalloc(size_t bytes)
{
	T_PTR	temp;

	temp = xmalloc(bytes);
	ft_memset(temp, 0, bytes);
	return (temp);
}

void
	xfree(void *obj0, void *obj1, void *obj2, void *obj3)
{
	if (obj0)
		free(obj0);
	if (obj1)
		free(obj1);
	if (obj2)
		free(obj2);
	if (obj3)
		free(obj3);
}

pid_t
	xfork(void)
{
	g_status.haschild = fork();
	if (g_status.haschild == ERROR)
		report_error_fatal(errno);
	return (g_status.haschild);
}

int
	xexecve(const char *file, char *const *argv, char *const *envp)
{
	int	result;

	result = OK;
	if (execve(file, argv, envp) == ERROR)
	{
		if (report_error(argv[0], NULL, errno) == ENOENT)
			result = ES_NOTFOUND;
		result = ES_NOEXEC;
	}
	exit(result);
}
