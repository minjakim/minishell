/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by snpark            #+#    #+#             */
/*   Updated: 2021/12/03 10:38:56 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "resource.h"
# include "type.h"

int	initialize(t_shell *mini);
/*parse_envp.c*/
int parse_envp(t_env *env);
int replace_envp(t_env *env, int flag);

/*minishell.c*/
int minishell(t_shell *mini);

/*parse_line.c*/
int	parse_line(t_shell *mini);

/*make_cmd.c*/
int	make_cmd(t_shell *mini);

/*execute_cmd.c*/
int	execute_cmd(t_shell *mini);
/*general.c*/
int legal_variable_starter(char c);
int legal_variable_char(char c);
int legal_identifier (char *name);
int assignment (const char *string);
t_hash *check_declare_key(t_hash *head, char *key);
/*make_envp.c*/
void free_envp(char **envp);
int envplen(t_hash *handle);
int make_envp(char **new_envp, t_hash *handle);
/*declare.c*/
int	make_declare_head(t_hash **head, t_hash *back, t_hash tmp);
int make_declare(t_hash *back, t_hash tmp);
int add_declare_unit(t_hash **head, t_hash *back, t_hash tmp);
int add_declare(t_hash **head, char *str, int flag);
/*edit_declare_value.c*/
int edit_declare_value(char *value, t_hash *hash, int flag);

/*builtins*/
/*mini_env.c*/
int print_envp(char **envp);
int mini_env(t_shell *mini);
/*mini_export.c*/
int print_export(t_hash *handle);
int mini_export(t_shell *mini);
/*mini_unset.c*/
int remove_declare(t_hash **head, char *key);
int mini_unset(t_shell *mini);
/*mini_pwd.c*/
int mini_pwd(t_shell *mini);
/*mini_cd.c*/
int mini_cd(t_shell *mini);
#endif
