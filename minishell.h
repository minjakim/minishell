/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:02:00 by snpark            #+#    #+#             */
/*   Updated: 2021/09/17 16:48:07 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <string.h> /* strdup() 쓰려고 붙임*/
# include <stdio.h>
typedef struct	s_env t_env;

typedef	struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}		t_env;

t_env	*update_env(char *str, t_env *head, int	flag);
t_env	*parent_env(char **old_env);

#endif
