/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:31:08 by snpark            #+#    #+#             */
/*   Updated: 2021/09/19 17:33:32 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_list;

int
	main(int argc, char **argv, char **envp)
{
	char buffer[256];

	while(1)
	{
		read(0, buffer, 256);
		printf("%s", buffer);
		memset(buffer, 0 ,256);
	}
}
