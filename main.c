/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:31:08 by snpark            #+#    #+#             */
/*   Updated: 2021/09/18 16:05:31 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_list;

int
	main(int argc, char **argv, char **envp)
{
	char	*line;

	while(1)
	{
		if (prompt(&line) != 0)
			continue;
		printf("%s", line);
	}
}
