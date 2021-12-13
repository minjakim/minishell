/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:23:02 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/13 16:46:22 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include <termios.h>

typedef struct s_shell		t_shell;
typedef struct s_command	t_command;
typedef struct termios		t_termios;
typedef unsigned long		t_op;
typedef unsigned char		t_byte;

typedef struct s_globvector
{
	struct s_globvector	*next;
	char				*str;
}	t_globvector;

typedef struct s_word_desc
{
	char				*word;
	int					flags;
}	t_word_desc;

typedef struct s_word_list
{
	struct s_word_list	*next;
	t_word_desc			word;
}	t_word_list;

typedef union u_redirectee
{
	int					dest;
	t_word_desc			filename;
}	t_redirectee;

typedef struct s_redirect
{
	struct s_redirect	*next;
	int					redirector;
	int					flags;
	t_redirectee		redirectee;
	char				*here_doc_eof;
}	t_redirect;

typedef union u_io
{
	struct
	{
		int				in;
		int				out;
	};
	int					fd[2];
	long long			init;
}	t_io;

typedef struct s_command
{
	int					flags;
	t_redirect			*redirects;
	t_word_list			*words;
	t_io				io;
	char				*path;
	char				**argv;
	t_command			*next;
	int					connector;
}	t_command;

typedef struct s_declare
{
	char				*key;
	char				*value;
	int					flag;
	struct s_declare	*next;
}	t_declare;

typedef struct s_env
{
	t_declare			*declare;
	char				**envp;
}	t_env;

typedef struct s_status
{
	t_io				heredoc;
	int					interactive;
	int					exit;
	int					error;
}	t_status;

typedef struct s_buffer
{
	char				*line;
	t_word_list			*words;
}	t_buffer;

typedef struct s_backup
{
	t_termios			attr;
	t_io				stdio;
}	t_backup;

struct s_shell
{
	t_backup			backup;
	t_status			*status;
	t_env				env;
	t_command			*command;
	int					(*execute[9])(t_shell *);
};

#endif
