/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:23:02 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/10 13:32:56 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include <termios.h>

/*word desc flags*/
#define W_HASHDOLLAR		0x00000001
#define W_QUOTED			0x00000002
#define W_DQUOTED			0x00000004
#define W_NOSPLIT			0x00000008
#define W_GLOBEXP			0x00000010
#define W_NOGLOB			0x00000020
#define W_TILDEEXP			0x00000040
#define W_ITILDE			0x00000080
#define W_NOEXPAND			0x00000100
#define W_ASSNBLTIN			0x00000200
#define W_ASSIGNARG			0x00000400
#define W_HASHQUOTEDNULL	0x00000800

#define W_PIPE				0x00001000
#define W_REDIRECT			0x00002000
#define W_HEREDOC			0x00004000
#define	W_CONTROL			0x00008000

#define	W_FILENAME			0x00010000
#define	W_ARG				0x00020000
#define W_AND_AND			0x00040000
#define	W_OR_OR				0x00080000
#define W_GRATER			0x00100000
#define W_GRATER_GRATER		0x00200000
#define W_LESS				0x00400000
#define	W_LESS_LESS			0x00800000

typedef struct s_shell	t_shell;

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

/*redirect*/

typedef union	u_redirectee
{
	int			dest;
	t_word_desc	filename;
}	t_redirectee;

typedef struct	s_redirect
{
	struct s_redirect	*next;
	int					redirector;
	int					flags;
	t_redirectee		redirectee;
	char				*here_doc_eof;
}	t_redirect;

/*command*/

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

typedef struct	s_simple
{
	t_redirect	*redirects;
	t_word_list	*words;
	t_io		io;
	char		*path;
	char		**argv;
}	t_simple;

typedef struct	s_connection
{
	t_redirect			*redirects;
	t_word_list			*words;
	t_io				io;
	char				*path;
	char				**argv;
	struct s_command	*next;
	int					connector;
}	t_connection;

typedef union	u_cmd_type
{
	t_simple		simple;
	t_connection	connection;
}	t_cmd_type;

typedef	enum	e_command_type
{
	cm_simple,
	cm_connection,
}	t_command_type;

typedef struct	s_command
{
	int				flags;
	t_command_type	type;
	t_cmd_type		value;
}	t_command;

typedef struct s_termios
{
	struct termios	current;
	struct termios	backup;
}	t_termios;

/*hash*/
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

typedef struct	s_status
{
	int			interactive;
	int			exit;
	int			error;
}	t_status;

typedef struct	s_buffer
{
	char		*line;
	t_word_list	*node;
}	t_buffer;

/*shell*/

struct s_shell
{
	t_termios	config;
	t_io		backup;
	t_env		env;
	t_command	*cmd;
	t_status	status;
	int			(*execute[9])(t_shell *);
};

#endif
