/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by snpark            #+#    #+#             */
/*   Updated: 2021/12/17 11:11:04 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "resource.h"
# include "type.h"
# include "temp.h"

extern t_status	g_status;

T_PTR		xmalloc(size_t bytes);
int			initialize(t_shell *mini);

void		eof_exit(t_shell *mini);
int			mini_exit(int exit_status);
int			envp_update(t_env *env, int flag);
t_word_list	*word_list_handler(char *line);
int			word_list_flag(t_word_list *words);
t_word_list	*word_list_free(t_word_list *words);

int			command_handler(t_word_list *words, t_shell *mini);
int			command_find(t_shell *mini);
void		command_clean(t_shell *mini);
int			command_execute(t_shell *mini);
int			command_redirect(t_shell *mini);
int			command_heredoc(t_command *command);
void		command_io_close(t_io *io);
int			command_io_set(t_io *io);
int			command_pipe_set(t_shell *mini);

void		sigint_handler(int signum);
void		signal_handler(int signum);
int			envp_handler(t_env *env);

int			exception_error_fatal(const int err_no);
int			exception_error(const char *const cmd, \
									const char *const arg, const int err_no);
int			exception_report(const char *cmd, const char *const arg, \
								const char *const msg, const int error_no);

int			expand_command(t_shell *mini);
int			expand_word(t_word_desc *desc);
char		**expand_glob(t_word_desc *word);
char		*expand_teilde(char *filename, int i);

int			declare_remove(t_declare **head, const char *const key);
int			declare_add(t_declare **head, char *str, int flag);
int			declare_edit(char *value, t_declare *declare, int flag);

int			mini_execve(const t_command *const command);
int			builtin_cd(const t_command *const command);
int			builtin_echo(const t_command *const command);
int			builtin_env(const t_command *const command);
int			builtin_exit(const t_command *const command);
int			builtin_export(const t_command *const command);
int			builtin_pwd(const t_command *const command);
int			builtin_unset(const t_command *const command);
int			mini_null(const t_command *const command);

int			is_quote(const char c, int quote);
int			is_teilde(const char *const str, int i, int quote);
int			is_builtin(const char *str);

int			legal_variable_starter(const char c);
int			legal_variable_char(const char c);
int			declare_check(const char *str);
void		remove_quote(char *str);

void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *sdt, const void *src, size_t n);
char		*ft_strdup(const char *s1);
char		*ft_strndup(const char *s1, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_strcat(char *s1, const char *s2);
size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_strmove(char *dest, char *src, int len);
#endif
