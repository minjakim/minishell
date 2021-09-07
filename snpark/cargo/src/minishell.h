/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:02:00 by snpark            #+#    #+#             */
/*   Updated: 2021/09/07 18:23:29 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct	s_env t_env;

typedef	struct s_env
{
	char	*env;
	t_env	*next;
}		t_env;

typedef struct s_envp
{
	char	**old_env;
	t_env	*new_env;
}		t_envp;

#endif
