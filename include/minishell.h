/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by snpark            #+#    #+#             */
/*   Updated: 2021/10/19 22:02:12 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "resource.h"
# include "type.h"


int parse_env(char ***original_envp);
int parse_line(char *line);

int	shell_execve(t_command cmd, char **env);

int ft_execve(char **argv, char **envp);

int	redirect(t_command *cmd);
/*
**builtin function
*/
int	builtin_echo(char **argv, char **envp, t_io stream);
int	cd(char **argv, char **envp);
int	pwd(char **argv, char **envp, int stream_out);
int	ms_export(char **argv, char **envp, t_io stream);
t_key_value_idx ms_getenv(char *key, char **envp);
int	find_offset(char *str);
int	ms_unset(char **argv, char **envp);
int	ms_env(char **argv, char **envp, int stream_out);
int	ms_exit(int	exit_status);
int	legal_identifier(char *name);

#endif
