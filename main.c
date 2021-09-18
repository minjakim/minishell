/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:31:08 by snpark            #+#    #+#             */
/*   Updated: 2021/09/18 14:28:14 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_list;

int
	main(int argc, char **argv, char **envp)
{
	char	buffer[256];
	int		read_len;

	while(1)
	{
		write(1, "> ", 2);
		usleep(100000);
		memset(buffer, 0, sizeof(char) * 256);
		read_len = read(0, buffer, 256);
		printf("%s", buffer);
	}
}
