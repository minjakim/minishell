/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:25:20 by minjakim          #+#    #+#             */
/*   Updated: 2021/10/19 20:50:29 by minjakim         ###   ########.fr       */
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
# include "../lib/bash-3.2.57/command.h"

//pid_t
# include <sys/types.h>
//ARG_MAX
# include <limits.h>
//strdup
# include <string.h>

# define PROMPT "mini ^o^)/ $> "


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
