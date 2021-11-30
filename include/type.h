/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:23:02 by minjakim          #+#    #+#             */
/*   Updated: 2021/11/30 12:10:30 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include <termios.h>

typedef struct s_command	t_command;
typedef struct s_file		t_file;
typedef struct s_hash t_hash;

//typedef struct word_desc {
//  char *word;		/* Zero terminated string. */
//  int flags;		/* Flags associated with this word. */
//} WORD_DESC;

///* A linked list of words. */
//typedef struct word_list {
//  struct word_list *next;
//  WORD_DESC *word;
//} WORD_LIST;


typedef struct s_curses
{
	int		row;
	int		column;
	char	*move;
}	t_curses;

typedef struct s_termios
{
	struct termios	current;
	struct termios	backup;
}	t_termios;

typedef struct	s_word
{
	int		expand;
	char	*word;
}	t_word;
/*
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
*/

typedef	struct s_valiable
{
	char	*shell;
	char	*env;
}	t_valiable;

typedef struct s_shell
{
	t_termios	config;
	t_curses	curses;
	t_command	*cmd_list;
}	t_shell;

typedef struct s_hash
{
	char	*key;
	char	*value;
	t_hash	*next;
}	t_hash;

typedef

#endif
