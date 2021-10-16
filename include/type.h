/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:23:02 by minjakim          #+#    #+#             */
/*   Updated: 2021/10/15 18:18:30 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

typedef struct	s_command t_command;
typedef struct	s_file t_file;

typedef struct	s_word
{
	int		expand;
	char	*word;
}	t_word;

typedef struct s_line
{
	int		flags;
	char 	*data;
}	t_line;

typedef union u_io
{
	struct
	{
		int		in;
		int		out;
	};
	int			fd[2];
	long long	init;
}	t_io;

typedef struct s_file
{
	char	*file;
	char	redirection;
	t_file	*next;
}	t_file;

typedef struct s_io_file
{
	t_file	*in;
	t_file	*out;
}	t_io_file;

typedef struct	s_command
{
	char		**argv;
	t_io		stream;
	t_io_file	file;
	t_io		pipe;
	t_command	*next;
}	t_command;

typedef struct s_key_value_idx
{
	int	key;
	int	value;
}	t_key_value_idx;

typedef	struct s_valiable
{
	char	*shell;
	char	*env;
}	t_valiable;

typedef struct s_shell
{
	t_line	line;

}	t_shell;

#endif
