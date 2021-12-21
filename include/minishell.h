/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by snpark            #+#    #+#             */
/*   Updated: 2021/12/20 21:44:12 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "resource.h"
# include "type.h"

extern t_status	g_status;

T_PTR		xcalloc(size_t bytes);
T_PTR		xcalloc_t_command(void);
pid_t		xfork(void);
void		xfree(void *obj);
void		xwait(pid_t pid);
int			xpipe(int fd[2], const char *const str);
void		disposer(void *obj0, void *obj1, void *obj2, void *obj3);

int			initialize(void);
int			declare_init(void);
int			declare_update_envp(void);
t_declare	*declare_add(const char *str);

int			is_builtin(const char *str);

char		mini_readline(char **line);
void		handling_eof(void);
int			mini_exit(int exit_status);

t_word_list	*parse_line(char *line);
int			make_words(t_word_list *words);
t_command	*parse_words(t_word_list *words);
int			make_heredoc(const t_command *cmd);
int			find_command(t_command *cmd);
int			execute_handler(t_command *cmd);
int			redirect_io(t_command *cmd);
void		set_io(const t_io *const io);
void		close_io(const t_io *const io);
void		reset_io(const t_io *const io);

void		dispose_cmd(t_command *cmd);
void		dispose_argv(char **argv);
void		*dispose_words(t_word_list *words);

void		sigint_handler(int signum);
void		signal_handler(int signum);
void		signal_report(int signum);
int			event_hook(void);

char		*expand_str(char *src, int heredoc);
char		**expand_glob(t_word_desc *word);
char		*expand_teilde(char *filename, int i);

int			expand_command(t_command *cmd);
void		remove_quote(char *str);

int			is_quote(const char c, int quote);
int			is_teilde(const char *const str, int i, int quote);

int			legal_variable_starter(const char c);
int			legal_variable_char(const char c);
int			declare_check(const char *str);

char		*remove_quote(char *str);

int			report_error(const char *const cmd, \
									const char *const arg, const int error);
int			report_error_fatal(const int error);
int			report_error_syntax(const char *const token);
int			report_exception(const char *cmd, const char *const arg, \
								const char *const report, const int status);
int			report_exception_fatal(const char *const report, const int status);

int			mini_execve(const t_command *const cmd);
int			builtin_cd(const t_command *const cmd);
int			builtin_echo(const t_command *const cmd);
int			builtin_env(const t_command *const cmd);
int			builtin_exit(const t_command *const cmd);
int			builtin_export(const t_command *const cmd);
int			builtin_pwd(const t_command *const cmd);
int			builtin_unset(const t_command *const cmd);
int			mini_null(const t_command *const cmd);

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
