/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:02:00 by snpark            #+#    #+#             */
/*   Updated: 2021/09/20 17:33:47 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <string.h> /* strdup() 쓰려고 붙임*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
typedef struct	s_env t_env;

typedef	struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}		t_env;

t_env	*ft_export(char *str, t_env *head, int	flag);
t_env	*parent_env(char **old_env);
int		env(t_env *list);
int		pwd();
int		echo(char *str, char flag);
int		cd(char *path);
int		unset(const char *key);
int		ft_exit(int error_number);

int		prompt(char **line);

#endif
