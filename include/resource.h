/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:25:20 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/20 21:04:36 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCE_H
# define RESOURCE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <termcap.h>
# include <sys/cdefs.h>
# include <signal.h>
# include "../lib/readline_arm64/include/readline.h"
# include "../lib/readline_arm64/include/history.h"
# include <limits.h>

# define PROMPT					"mini ^o^)/ $> "
# define SECOND					"> "
# define T_PTR					void *
# define LOMAGIC				0x0101010101010101
# define HIMAGIC				0x8080808080808080
# define OPSIZ					8
# define LOOP					1
# define HEREDOC_MAX			16

# define HOME					"HOME"
# define PATH					"PATH"
# define PWD					"PWD"
# define OLDPWD					"OLDPWD"

# define EXIT					"exit\n"
# define EX_EXIT_FMT			"numeric argument required"
# define EX_EXIT_ARGS			"too many arguments"
# define EX_CD_HOME				"HOME not set"
# define EX_CD_OLDPWD			"OLDPWD not set"
# define EX_SYNTAX				"syntax error near unexpected token"
# define EX_HEREDOC_MAX			"maximum here-docment count exceeded"
# define EX_CMD_NOTFOUND		"command not found"
# define EX_DECLARE				"not a valid identifier"
# define EX_AMBIGUAS			"ambiguous redirect"

# define ES_BADUSAGE			2
# define ES_NOEXEC				126
# define ES_NOTFOUND			127
# define ES_EXIT_FMT			255
# define ES_USAGE				258

# define CMD_COMMAND_BUILTIN	0x00000001
# define CMD_STDIN_REDIR		0x00000002
# define CMD_STDOUT_REDIR		0x00000004
# define CMD_NO_FORK			0x00000008
# define CMD_INHIBIT_EXPANSION	0x00000010
# define CMD_NOFUNCTION			0x00000020
# define CMD_IGNORE_RETURN		0x00000040
# define CMD_PIPE				0x00000080
# define CMD_SUBSHELL			0x00000100

# define W_NOFLAG				0
# define W_HASHDOLLAR			0x00000001
# define W_QUOTED				0x00000002
# define W_DQUOTED				0x00000004
# define W_NOSPLIT				0x00000008
# define W_GLOBEXP				0x00000010
# define W_NOGLOB				0x00000020
# define W_TILDEEXP				0x00000040
# define W_ITILDE				0x00000080
# define W_NOEXPAND				0x00000100
# define W_ASSNBLTIN			0x00000200
# define W_ASSIGNARG			0x00000400
# define W_HASHQUOTEDNULL		0x00000800

# define W_PIPE					0x00001000
# define W_REDIRECT				0x00002000
# define W_HEREDOC				0x00004000
# define W_CONTROL				0x00008000

# define W_FILENAME				0x00010000
# define W_ARG					0x00020000
# define W_AND_AND				0x00040000
# define W_OR_OR				0x00080000
# define W_GRATER				0x00100000
# define W_GRATER_GRATER		0x00200000
# define W_LESS					0x00400000
# define W_LESS_LESS			0x00800000
# define W_EXITSTATUS			0x01000000

# define H_EXPORT				1
# define H_KEYONLY				2
# define H_CAT					4

enum e_bool
{
	FALSE,
	TRUE
};

enum e_return
{
	EXCEPTION = -2,
	ERROR,
	FAILURE,
	SUCCESS
};

enum e_exit_status
{
	OK,
	GENERAL_ERROR
};

#endif
