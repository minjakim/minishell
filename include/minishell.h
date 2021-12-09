/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by snpark            #+#    #+#             */
/*   Updated: 2021/12/09 12:12:49 by minjakim         ###   ########.fr       */
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
int redirect_stdio(t_io io);
int	ft_execve(t_shell *mini);
/*expand_cmd.c*/
int expand_cmd(t_shell *mini);
/*expand_word.c*/
int expand_word(t_word_desc *desc);
void remove_quote(char *str);
/*ft_teilde_expand.c*/
int is_teilde(const char *const str, int i, int quote);
char *ft_teilde_expand(char *filename, int i);
/*redirect.c*/
int redirect(t_shell *mini);
/*general.c*/
int legal_number(const char *str);
int legal_variable_starter(const char c);
int legal_variable_char(const char c);
int legal_identifier (const char *name);
int assignment (const char *string);
/*make_envp.c*/
void free_envp(char **envp);
int envplen(t_hash *handle);
int make_envp(char **new_envp, t_hash *handle);
/*declare.c*/
t_hash *check_declare_key(t_hash *head, const char *const key);
int	make_declare_head(t_hash **head, t_hash *back, t_hash tmp);
int make_declare(t_hash *back, t_hash tmp);
int add_declare_unit(t_hash **head, t_hash *back, t_hash tmp);
int add_declare(t_hash **head, char *str, int flag);
/*edit_declare_value.c*/
int edit_declare_value(char *value, t_hash *hash, int flag);
/*glob.c*/
char **glob_expand(t_word_desc *word);
/*builtins*/
/*mini_env.c*/
int print_envp(const char **envp);
int mini_env(t_shell *mini);
/*mini_export.c*/
int print_export(t_hash *handle);
int mini_export(t_shell *mini);
/*mini_unset.c*/
int remove_declare(t_hash **head, const char *const key);
int mini_unset(t_shell *mini);
/*mini_pwd.c*/
int mini_pwd(t_shell *mini);
/*mini_cd.c*/
int mini_cd(t_shell *mini);
/*mini_echo.c*/
int	mini_echo(t_shell *mini);
/*mini_exit.c*/
long long mini_strtoll(const char *str);
int	mini_exit(t_shell *mini);
int	mini_null(t_shell *mini);

/*strmove.c*/
void strmove(char *dest, char *src, int len);
#endif
