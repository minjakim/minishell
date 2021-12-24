/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:23:02 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/20 21:03:28 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include <termios.h>
# include <sys/types.h>

typedef struct s_command	t_command;
typedef struct termios		t_termios;
typedef unsigned long		t_op;
typedef unsigned char		t_byte;

typedef enum e_execute
{
	NOTFOUND,
	MINI_NULL,
	FT_CD,
	FT_ECHO,
	FT_ENV,
	FT_EXIT,
	FT_EXPORT,
	FT_PWD,
	FT_UNSET,
	MINI_EXECVE
}	t_execute;

typedef struct s_tuple
{
	char		*d;
	const char	*s;
}	t_tuple;

typedef struct s_globvector
{
	struct s_globvector	*next;
	char				*str;
}	t_globvector;

typedef struct s_word_desc
{
	union
	{
		char			*word;
		char			*eof;
	};
	int					flags;
}	t_word_desc;

typedef struct s_word_list
{
	struct s_word_list	*next;
	t_word_desc			word;
}	t_word_list;

typedef struct u_redirectee
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
}	t_redirect;

typedef union u_io
{
	struct
	{
		int				in;
		int				out;
	};
	int					fd[2];
	long long			value;
}	t_io;

typedef struct s_command
{
	int					flags;
	int					connector;
	t_redirect			*redirects;
	t_word_list			*words;
	t_io				io;
	char				*path;
	char				**argv;
	int					argc;
	t_execute			type;
	t_command			*next;
}	t_command;

typedef struct s_str
{
	char				*str;
	size_t				len;
}	t_str;

typedef struct s_declare
{
	struct s_declare	*prev;
	t_str				key;
	t_str				value;
	char				*line;
	int					exported;
	struct s_declare	*next;
}	t_declare;

typedef struct s_env
{
	int					edited;
	char				**envp;
	int					envc;
	t_declare			*head;
	t_declare			*tail;
}	t_env;

typedef struct s_backup
{
	t_termios			attr;
	t_io				stdio;
}	t_backup;

typedef struct s_state
{
	union
	{
		struct
		{
			char		error;
			char		interrupted;
			char		need_heredoc;
			char		readline;
		};
		int				any;
	};
	int					prompt;
	pid_t				haschild;
}	t_state;

typedef struct s_status
{
	volatile t_state	state;
	int					interactive;
	int					exit;
	t_env				env;
	t_io				heredoc;
	t_backup			backup;
	int					(*execute[10])(const t_command *);
}	t_status;
#endif
