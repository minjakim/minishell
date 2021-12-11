/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by snpark            #+#    #+#             */
/*   Updated: 2021/12/11 10:44:30 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "resource.h"
# include "type.h"
# include "temp.h"

int		initialize(t_shell *mini);
int 	minishell(t_shell *mini);

int		parse_envp(t_env *env);
int		parse_line(t_buffer *buffer);
int		replace_envp(t_env *env, int flag);

int		make_cmd(t_word_list *words, t_shell *mini);
int		find_cmd(t_shell *mini);
void	clean_cmd(t_shell *mini);

void	handler_signal(int signum);
void	handler_eof(t_shell *mini);

int		execute_cmd(t_shell *mini);
int		ft_execve(t_shell *mini);
int		redirect_stdio(t_io *io);

int		redirect(t_shell *mini);
int		expand_cmd(t_shell *mini);
int		expand_word(t_word_desc *desc);
char	**glob_expand(t_word_desc *word);

char	*ft_teilde_expand(char *filename, int i);
void	remove_quote(char *str);

int		is_builtin(const char *str);
int		is_teilde(const char *const str, int i, int quote);
int		is_quote(const char c, int quote);
int		is_key(const char *str, const int i, const int quote);

int		legal_number(const char *str);
int		legal_variable_starter(const char c);
int		legal_variable_char(const char c);
int		legal_identifier (const char *name);
int		assignment (const char *string);

void	free_envp(char **envp);
int		envplen(t_hash *handle);
int		make_envp(char **new_envp, t_hash *handle);

t_hash	*declare_check_key(t_hash *head, const char *const key);
int		declare_make_head(t_hash **head, t_hash *back, t_hash tmp);
int		declare_make(t_hash *back, t_hash tmp);
int		declare_remove(t_hash **head, const char *const key);
int		declare_add_unit(t_hash **head, t_hash *back, t_hash tmp);
int		declare_add(t_hash **head, char *str, int flag);
int		declare_edit_value(char *value, t_hash *hash, int flag);

int		print_envp(const char **envp);
int		print_export(t_hash *handle);
int		builtin_env(t_shell *mini);
int		builtin_export(t_shell *mini);
int		builtin_unset(t_shell *mini);
int		builtin_pwd(t_shell *mini);
int		builtin_cd(t_shell *mini);
int		builtin_echo(t_shell *mini);
int		builtin_exit(t_shell *mini);
int		builtin_null(t_shell *mini);

void	ft_strmove(char *dest, char *src, int len);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(char *sdt, const char*src, size_t n);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);

#endif
