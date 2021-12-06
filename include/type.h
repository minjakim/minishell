/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */ /*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:23:02 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/05 20:56:20 by snpark           ###   ########.fr       */
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
#define W_GLOBEXP			0x0000000f
#define W_NOGLOB			0x00000010
#define W_TILDEEXP			0x00000020
#define W_ITILDE			0x00000040
#define W_NOEXPAND			0x00000080
#define W_ASSNBLTIN			0x000000f0
#define W_ASSIGNARG			0x00000100
#define W_HASHQUOTEDNULL	0x00000200

#define W_PIPE				0x00000400
#define W_REDIRECT			0x00000800
#define W_HEREDOC			0x00000f00
#define	W_CONTROL			0x00001000

#define	W_FILENAME			0x00002000
#define	W_ARG				0x00004000

typedef struct s_word_desc
{
	char	*word;
	int		flags;
}	t_word_desc;

typedef struct s_word_list
{
	struct s_word_list	*next;
	t_word_desc			*word;
}	t_word_list;

/*redirect*/

typedef union	u_redirectee
{
	int			dest;
	t_word_desc	*filename;
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

/*error*/
typedef struct s_error
{
	char	*bash;
	char	*cmd;
	char	*arg;
	char	*message;
	int		exit_status;
	int		error;
}	t_error;

/*shell*/

typedef struct s_shell
{
	int			stdin;
	int			stdout;
	t_env		env;
	char		*line;
	t_word_list	*list;
	t_command	*cmd;
	t_error		err;
	int			interactive;
}	t_shell;

#endif
