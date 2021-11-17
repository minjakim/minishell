/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by snpark            #+#    #+#             */
/*   Updated: 2021/11/15 17:23:48 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "resource.h"
# include "type.h"


int parse_env(char ***original_envp, t_hash **export_list);
void add_export_list(char *str, t_hash **list);
int parse_line(char *line);

int	shell_execve(t_command cmd, char **env, t_hash **export_list, int *exis_status);

int ft_execve(char **argv, char **envp, int *exit_status);

int	redirect(t_command *cmd, int *exit_status);
/*
**builtin function
*/
int	builtin_echo(char **argv, t_io stream, int *exit_status);
int	cd(char **argv, char **envp, int *exit_status);
int	pwd(int stream_out, int *exit_status);
int ms_export(t_command cmd, char **envp, t_hash **ex_list, int *exit_status);
t_key_value_idx ms_getenv(char *key, char **envp);
int	find_offset(char *str);
int	ms_unset(char **argv, char **envp, t_hash **ex_list, int *exit_status);
int	ms_env(char **argv, char **envp, int stream_out, int *exit_status);
int	ms_exit(char **argv, t_io pipe, int *exit_status);
int	legal_identifier(const char *cmd, char *name);
/*tmp*/
t_command *make_cmd(void);
/*error print
 * need to move from excute_cmd.c to another file*/
void bash_arg_err(const char *arg);
void bash_cmd_arg_err(const char *cmd, const char *arg);
void cmd_arg_err(const char *cmd, const char *arg);
#endif
