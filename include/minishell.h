/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:18:07 by snpark            #+#    #+#             */
/*   Updated: 2021/12/24 22:21:16 by minjakim         ###   ########.fr       */
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
void		xwait(pid_t pid, const t_io *const io);
int			xpipe(int fd[2], const char *const str);
void		disposer(void *obj0, void *obj1, void *obj2, void *obj3);

void		init_signal(void);
void		init_declare(void);
void		init_status(void);
void		make_declare(void);

void		declare_update_envp(void);
void		declare_update_node(const char *const key, const char *const value);
void		declare_export_new(const char *key, const char *after);
int			declare_export_update_value(t_declare *node, char *str);
char		*declare_new_line(const t_str *const key, const t_str *const value);
t_declare	*declare_new(const char *const str);
t_declare	*declare_add(const char *const str);
t_declare	*declare_search(const char *const str);
char		*declare_get_value(const char *const str);
int			declare_legal_check(const char *str);

char		mini_readline(char **line);
void		handling_eof(void);

t_word_list	*parse_line(char *line);
int			make_words(t_word_list *words);
t_command	*parse_words(t_word_list *words);
int			make_heredoc(const t_command *cmd);
int			execute_handler(t_command *cmd);
int			redirect_io(t_command *cmd);
int			find_command(t_command *cmd);

void		set_io(const t_io *const io);
void		close_io(const t_io *const io);
void		reset_io(const t_io *const io);

void		dispose_command(t_command *cmd);
void		*dispose_words(t_word_list *words);
void		dispose_argv(char **argv);

void		sigint_handler(int signum);
void		signal_handler(int signum);
void		signal_report(int signum);
int			signal_event_hook(void);

int			expand_command(t_command *cmd);
char		*expand_str(char *src, int heredoc);
int			expand_glob_argv(t_word_list *word, char *pattern, int *argc);
char		*expand_glob_filename(char *pattern);
char		*get_match_string(struct dirent *entry, const char *const pat);
int			glob_check_dir(const char *pat, const int type);
int			glob_strmatch(const char *pat, const char *str);

int			legal_variable_starter(const char c);
int			legal_variable_char(const char c);
char		*remove_quote(char *str);
int			is_quote(const char c, int quote);

int			report_error(const char *const cmd, \
									const char *const arg, const int error);
int			report_error_fatal(const int error);
int			report_error_syntax(const char *const token);
int			report_exception(const char *cmd, const char *const arg, \
								const char *const report, const int status);
int			report_exception_fatal(const char *const arg, \
									const char *const report, const int error);

int			mini_null(const t_command *const cmd);
int			builtin_cd(const t_command *const cmd);
int			builtin_echo(const t_command *const cmd);
int			builtin_env(const t_command *const cmd);
int			builtin_exit(const t_command *const cmd);
int			builtin_export(const t_command *const cmd);
int			builtin_pwd(const t_command *const cmd);
int			builtin_unset(const t_command *const cmd);
int			mini_execve(const t_command *const cmd);
int			mini_exit(int exit_status);

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
char		*ft_itoshlvl(int n);
int			ft_shlvltoi(const char *str);

#endif
