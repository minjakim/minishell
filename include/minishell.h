/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by snpark            #+#    #+#             */
/*   Updated: 2021/12/14 16:24:55 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "resource.h"
# include "type.h"
# include "temp.h"

extern t_status	g_status;

int			initialize(t_shell *mini);

void		eof_exit(t_shell *mini);
int			envp_update(t_env *env, int flag);
t_word_list	*word_list_handler(char *line);

int			command_handler(t_word_list *words, t_shell *mini);
int			command_find(t_shell *mini);
void		command_clean(t_shell *mini);
int			command_execute(t_shell *mini);
int			command_redirect(t_shell *mini);
void		command_io_close(t_io *io);
int			command_io_set(t_io *io);
int			command_pipe_set(t_shell *mini);

void		sigint_handler(int signum);
void		signal_handler(int signum);

int			envp_handler(t_env *env);

int			expand_command(t_shell *mini);
int			expand_word(t_word_desc *desc);
char		**expand_glob(t_word_desc *word);
char		*expand_teilde(char *filename, int i);

int			declare_remove(t_declare **head, const char *const key);
int			declare_add(t_declare **head, char *str, int flag);
int			declare_edit(char *value, t_declare *declare, int flag);

int			is_quote(const char c, int quote);
int			is_teilde(const char *const str, int i, int quote);

int			legal_variable_starter(const char c);
int			legal_variable_char(const char c);
int			declare_check(const char *str);

int			mini_execve(t_command *command);
int			builtin_cd(t_command *command);
int			builtin_echo(t_command *command);
int			builtin_env(t_command *command);
int			builtin_exit(t_command *command);
int			builtin_export(t_command *command);
int			builtin_pwd(t_command *command);
int			builtin_unset(t_command *command);
int			mini_null(t_command *command);

void		error_fatal(const char *const str, const size_t nbyte);

void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(char *sdt, const char*src, size_t n);
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
