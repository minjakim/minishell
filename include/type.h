/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:23:02 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/11 18:41:52 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include <termios.h>

typedef struct s_shell		t_shell;
typedef struct s_command	t_command;
typedef unsigned long		t_op;
typedef unsigned char		t_byte;

typedef struct s_globvector
{
	struct s_globvector	*next;
	char				*str;
}	t_globvector;

typedef struct s_word_desc
{
	char	*word;
	int		flags;
}	t_word_desc;

typedef struct s_word_list
{
	struct s_word_list	*next;
	t_word_desc			word;
}	t_word_list;

typedef union u_redirectee
{
	int			dest;
	t_word_desc	filename;
}	t_redirectee;

typedef struct s_redirect
{
	struct s_redirect	*next;
	int					redirector;
	int					flags;
	t_redirectee		redirectee;
	char				*here_doc_eof;
}	t_redirect;

typedef	union	u_io
{
	struct
	{
		int		in;
		int		out;
	};
	int			fd[2];
	long long	init;
}	t_io;

typedef struct s_simple
{
	t_redirect	*redirects;
	t_word_list	*words;
	t_io		io;
	char		*path;
	char		**argv;
}	t_simple;

typedef struct s_connection
{
	t_redirect	*redirects;
	t_word_list	*words;
	t_io		io;
	char		*path;
	char		**argv;
	t_command	*next;
	int			connector;
}	t_connection;

typedef	enum e_command_type
{
	cm_simple,
	cm_connection,
}	t_command_type;

typedef struct s_command
{
	int				flags;
	t_command_type	type;
	union
	{
		t_simple		simple;
		t_connection	connection;
	}	value;
}	t_command;

typedef struct s_termios
{
	struct termios	current;
	struct termios	backup;
}	t_termios;

typedef struct s_ios
{
	t_io	current;
	t_io	backup;
}	t_ios;

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

typedef struct s_status
{
	int			interactive;
	int			exit;
	int			error;
}	t_status;

typedef struct s_buffer
{
	char		*line;
	t_word_list	*words;
}	t_buffer;

struct s_shell
{
	t_termios	config;
	t_ios		ios;
	t_env		env;
	t_command	*command;
	t_status	status;
	int			(*execute[9])(t_shell *);
};

#endif
