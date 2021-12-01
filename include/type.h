/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:23:02 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/01 12:12:23 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include <termios.h>

/*hash flag*/
# define	H_EXPORT	1
# define	H_KEYONLY	2
# define	H_CAT		4

typedef struct s_hash
{
	char			*key;
	char			*value;
	int				flag;
	struct s_hash	*next;
}	t_hash;

typedef struct s_env
{
	t_hash	*declare;
	char	**envp;
}	t_env;

typedef struct s_shell
{
	int			stdin;
	int			stdout;
	t_env		env;
}	t_shell;

#endif
