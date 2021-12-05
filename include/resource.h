/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:25:20 by minjakim          #+#    #+#             */
/*   Updated: 2021/12/05 10:49:37 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCE_H
# define RESOURCE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <termios.h>
# include <termcap.h>
# include <sys/cdefs.h>
# include "../lib/readline_arm64/include/readline.h"
# include "../lib/readline_arm64/include/history.h"
//# include "../lib/bash-3.2.57/command.h"

//pid_t
# include <sys/types.h>

# include <limits.h>

# define PROMPT "mini ^o^)/ $> "

# define CMD_COMMAND_BUILTIN		0x00000001
# define CMD_STDIN_REDIR			0x00000002
# define CMD_STDOUT_REDIR			0x00000004
# define CMD_NO_FORK				0x00000008
# define CMD_INHIBIT_EXPANSION		0x0000000f
# define CMD_NOFUNCTION				0x00000010
# define CMD_IGNORE_RETURN			0x00000020
# define CMD_PIPE					0x00000040

enum e_flag_exception
{
	single_quotes,
	double_quotes,
	back_slash,
	semicolon,
};

enum e_bool
{
	FALSE,
	TRUE
};

#endif
