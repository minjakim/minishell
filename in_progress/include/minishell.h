/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by snpark            #+#    #+#             */
/*   Updated: 2021/10/14 09:40:14 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>

//pid_t
# include <sys/types.h>

//ARG_MAX
# include <limits.h>
//strdup
# include <string.h>

typedef struct	s_command t_command;
typedef struct	s_file t_file;

typedef struct s_file
{
	char	*file;
	char	redirection;
	t_file	*next;
}				t_file;

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
}				t_command;

typedef struct s_key_value_idx
{
	int	key;
	int	value;
}				t_key_value_idx;

typedef	struct s_valiable
{
	char	*shell;
	char	*env;
}		t_valiable;

int parse_env(char ***original_envp);

int	shell_execve(t_command cmd, char **env);

int ft_execve(char **argv, char **envp);

int	redirect(t_command *cmd);
/*
**builtin function
*/
int	echo(char **argv, char **envp, int stream_in, int stream_out);
int	cd(char **argv, char **envp);
int	pwd(char **argv, char **envp, int stream_out);
int	ms_export(char **argv, char **envp, int stream_in, int strem_out);
t_key_value_idx ms_getenv(char *key, char **envp);
int	find_offset(char *str);
int	ms_unset(char **argv, char **envp);
int	ms_env(char **argv, char **envp, int stream_out);
int	ms_exit(int	exit_status);

#endif
