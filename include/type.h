/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:23:02 by minjakim          #+#    #+#             */
/*   Updated: 2021/10/15 11:23:47 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

typedef struct	s_command t_command;
typedef struct	s_file t_file;

typedef struct s_file
{
	char	*file;
	char	redirection;
	t_file	*next;
}	t_file;

typedef struct	s_command
{
	char	**argv;
	int		stream_out;
	int		stream_in;
	t_file	*out_file;
	t_file	*in_file;
	int		in_pipe;
	int		out_pipe;
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
}		t_valiable;

#endif
