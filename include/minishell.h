/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by snpark            #+#    #+#             */
/*   Updated: 2021/11/11 15:47:24 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "resource.h"
# include "type.h"


int parse_env(char ***original_envp, t_hash **export_list);
void add_export_list(char *str, t_hash **list);
int parse_line(char *line);

int	shell_execve(t_command cmd, char **env, t_hash **export_list);

int ft_execve(char **argv, char **envp);

int	redirect(t_command *cmd);
/*
**builtin function
*/
int	builtin_echo(char **argv, char **envp, t_io stream);
int	cd(char **argv, char **envp);
int	pwd(char **argv, char **envp, int stream_out);
int	ms_export(char **argv, char **envp, t_io stream, t_hash **ex_list);
t_key_value_idx ms_getenv(char *key, char **envp);
int	find_offset(char *str);
int	ms_unset(char **argv, char **envp, t_hash **ex_list);
int	ms_env(char **argv, char **envp, int stream_out);
int	ms_exit(int	exit_status);
int	legal_identifier(char *name);
/*tmp*/
t_command *make_cmd(void);
#endif
