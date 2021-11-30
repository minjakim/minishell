/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/11/30 12:14:45 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include <string.h>

//int
//	__sflush(FILE *fp)
//{
//	unsigned char	*p;
//	int				n;
//	int				t;
//
//	t = fp->_flags;
//	p = fp->_bf._base;
//	if ((!(t & __SWR)) || !p)
//		return (0);
//	n = fp->_p - p;
//	fp->_p = p;
//	fp->_w = 0;
//	if (!(t & (__SLBF | __SNBF)))
//		fp->_w = fp->_bf._size;
//	while (n > 0)
//	{
//		t = (*fp->_write)(fp->_cookie, (char *)p, n);
//		if (t <= 0)
//		{
//			fp->_flags |= __SERR;
//			return (EOF);
//		}
//		n -= t;
//		p += t;
//	}
//	return (0);
//}
//
//int
//	ft_fflush(FILE *fp)
//{
//	if (fp == NULL)
//		return (0);
//	if ((fp->_flags & (__SWR | __SRW)) == 0)
//	{
//		errno = EBADF;
//		return (EOF);
//	}
//	return (__sflush(fp));
//}
//
//static void
//	get_cursor_position(t_curses *curses)
//{
//	int		i;
//	char	buf[255];
//
//	write(1, "\033[6n", 4);
//	i = read(0, buf, 254);
//	buf[i] = '\0';
//	i = 1;
//	while (!((unsigned)buf[i] - 48 < 10))
//		++i;
//	while (((unsigned)buf[i] - 48) < 10)
//		curses->row = (curses->row << 1) + (curses->row << 3) + (buf[i++] - 48);
//}
//
//static int
//	putchar_tc(int tc)
//{
//	write(1, &tc, 1);
//	return (0);
//}
//
//static void
//	exit_eof_test(t_shell *mini, int exit_status)
//{
//	mini->config.current.c_lflag &= ~ICANON;
//	mini->config.current.c_lflag &= ~ECHO;
//	mini->config.current.c_cc[VMIN] = 1;
//	mini->config.current.c_cc[VTIME] = 0;
//	mini->curses.row = 0;
//	mini->curses.column = 0;
//	tcsetattr(STDIN_FILENO, TCSANOW, &mini->config.current);
//	get_cursor_position(&mini->curses);
//	tputs(tgoto(mini->curses.move, mini->curses.column += sizeof(PROMPT) - 1, mini->curses.row -= 2), 1, putchar_tc);
//	printf("exit\n");
//	tcsetattr(STDIN_FILENO, TCSANOW, &mini->config.backup);
//	exit(exit_status);
//}
//
//static void
//	sig_handler(int signum)
//{
//
//	if (signum != SIGINT)
//		return ;
//	write(STDOUT_FILENO, "\n", 1);
//	rl_on_new_line();
//	rl_replace_line("", 1);
//	rl_redisplay();
//}
//
//static void
//	initialize(t_shell *mini)
//{
//	tgetent(NULL, "xterm");
//	mini->curses.move = tgetstr("cm", NULL);
//	tcgetattr(STDIN_FILENO, &mini->config.current);
//	mini->config.backup = mini->config.current;
//	mini->config.current.c_cc[VQUIT] = 0;
//	tcsetattr(STDIN_FILENO, TCSANOW, &mini->config.current);
//	signal(SIGINT, sig_handler);
//	rl_catch_signals = 0;
//}
//
//static char 
//	*cat_3_str(char *first, char *second, char *third)
//{
//	char *dest;
//
//	dest = malloc(sizeof(char) * (strlen(first) + strlen(second) + strlen(third) + 1));
//	if (dest == NULL)
//		return (NULL);
//	while (*third != '\0' && *third != ' ')
//		third++;
//	strcpy(dest, first);
//	strcat(dest, second);
//	strcat(dest, third);
//	if (dest == NULL)
//		return (NULL);
//	return (dest);
//}
//
//static char
//	*replace_env_find_key(char *key, t_hash *export_list)
//{
//	int	i;
//
//	i = 0;
//	while(key[i] != ' ' && key[i] != '\0')
//		i++;
//	while (export_list)
//	{
//		if (strncmp(key, export_list->key, i) == 0)
//			return (export_list->value);
//		export_list = export_list->next;
//	}
//	return (NULL);
//}
//
//int
//	replace_env(char **str, int expand, t_hash *export_list)
//{
//	int		i;
//	char	*dest;
//	char	*tmp;
//	char	*value;
//
//	if (expand == 0)
//		return (0);
//	i = 0;
//	dest = strdup(*str);
//	if (dest == NULL)
//		return (-1);
//	tmp = NULL;
//	while(dest[i] != '\0')
//	{
//		if (dest[i] == '$')
//		{
//			dest[i++] = '\0';
//			value = replace_env_find_key(dest + i, export_list);
//			if (value == NULL)
//				return (-2);/*매칭 되는 환경 변수가 없을 때*/
//			tmp= cat_3_str(dest, value, dest + i);
//			if (tmp == NULL)
//				return (-1);
//			free(dest);
//			dest = tmp;
//		}
//		++i;
//	}
//	free(*str);
//	*str = dest;
//	return (0);
//}
//
//static int
//	excute_sub(t_command *cmd, char **envp, t_hash **export_list, int *exit_status)
//{
//	pid_t	pid;
//
//	if (cmd->pipe.out != -1)
//	{
//		pipe(cmd->pipe.fd);
//		cmd->pipe.out = cmd->pipe.fd[0];
//		cmd->next->pipe.in = cmd->pipe.fd[1];
//	}
//	pid = fork();
//	if (pid == 0)
//	{
//		if (cmd->pipe.out != -1)
//			dup2(cmd->pipe.out, 1);
//		if (cmd->pipe.in != -1)
//			dup2(cmd->pipe.in, 0);
//		//replace_env();
//		if (redirect(cmd, exit_status, *export_list) == -1)
//			return (-1);
//		shell_execve(*cmd, envp, export_list, exit_status);
//	}
//	else if (pid > 0)
//	{
//		if (cmd->pipe.in != -1 && cmd->pipe.out == -1)/*마지막 파이프 커맨드*/
//		{
//			waitpid(pid, exit_status, 0);/*파이프의 마지막 커맨드의 종료상태 반환*/
//			while(wait(NULL) != -1)/*자식프로세스가 없을 때까지 대기*/
//				;
//		}
//	}
//	return (0);
//}
//
//static int 
//	excute_main(t_command *cmd, char **envp, t_hash **export_list, int *exit_status)
//{
//	while (cmd)
//	{
//		if (!(cmd->pipe.in == -1 && cmd->pipe.out == -1))
//			excute_sub(cmd, envp, export_list, exit_status);
//		else//main
//		{
//			//replace_env(); 환경변수 치환하는 함수
//			if (redirect(cmd, exit_status, *export_list) == -1)
//				return (-1);
//			shell_execve(*cmd, envp, export_list, exit_status);
//		}
//		cmd = cmd->next;
//		//if (flag == "&&" && exit_status == 1)
//		//	exit();
//		//if (flag == "||" && exit_status == 0)
//		//	eixt();
//	}
//	return (0);
//}
//
//void
//	clear_argv(char **argv)
//{
//	int	i;
//
//	i = -1;
//	while (argv[++i])
//		free(argv[i]);
//	free(argv);
//}
//
//void
//	clear_cmd_list(t_command **cmd_list)
//{
//	t_command *handle;
//	t_command *tmp;
//
//	if (cmd_list == NULL || *cmd_list == NULL)
//		return ;
//	handle = *cmd_list;
//	while (handle)
//	{
//		if (handle->argv != NULL)
//			clear_argv(handle->argv);
//		if (handle->file.in != NULL)
//			;
//		if (handle->file.out!= NULL)
//			;
//		tmp = handle;
//		handle = handle->next;
//		free(tmp);
//	}
//	*cmd_list = NULL;
//}

int main(int argc, char **argv, char **envp)
{
	t_shell		mini;

	(void)&argc;
	(void)argv;
	initialize(&mini);
//	while (1)
//	{
//		line = readline(PROMPT);
//		if (line == NULL)
//			break ;
//		if (*(int *)line == 1953069157 && line[5] == '\0')
//		{
//			printf("exit\n");
//			tcsetattr(STDIN_FILENO, TCSANOW, &mini.config.backup);
//			return (errno);
//		}
//		add_history(line);
//		free(line);
//		cmd_list = make_cmd();
//		excute_main(cmd_list, envp, &export_list, &exit_status);//export_list인자 추가
//		clear_cmd_list(&cmd_list);
//	}
//	exit_eof_test(&mini, exit_status);
}




//static void
//shell_initialize ()
//{
//  char hostname[256];

//  /* Line buffer output for stderr and stdout. */
//  if (shell_initialized == 0)
//    {
//      sh_setlinebuf (stderr);
//      sh_setlinebuf (stdout);
//    }

//  /* Sort the array of shell builtins so that the binary search in
//     find_shell_builtin () works correctly. */
//  initialize_shell_builtins ();

//  /* Initialize the trap signal handlers before installing our own
//     signal handlers.  traps.c:restore_original_signals () is responsible
//     for restoring the original default signal handlers.  That function
//     is called when we make a new child. */
//  initialize_traps ();
//  initialize_signals (0);

//  /* It's highly unlikely that this will change. */
//  if (current_host_name == 0)
//    {
//      /* Initialize current_host_name. */
//      if (gethostname (hostname, 255) < 0)
//	current_host_name = "??host??";
//      else
//	current_host_name = savestring (hostname);
//    }

//  /* Initialize the stuff in current_user that comes from the password
//     file.  We don't need to do this right away if the shell is not
//     interactive. */
//  if (interactive_shell)
//    get_current_user_info ();

//  /* Initialize our interface to the tilde expander. */
//  tilde_initialize ();

//  /* Initialize internal and environment variables.  Don't import shell
//     functions from the environment if we are running in privileged or
//     restricted mode or if the shell is running setuid. */
//#if defined (RESTRICTED_SHELL)
//  initialize_shell_variables (shell_environment, privileged_mode||restricted||running_setuid);
//#else
//  initialize_shell_variables (shell_environment, privileged_mode||running_setuid);
//#endif

//  /* Initialize the data structures for storing and running jobs. */
//  initialize_job_control (0);

//  /* Initialize input streams to null. */
//  initialize_bash_input ();

//  initialize_flags ();

//  /* Initialize the shell options.  Don't import the shell options
//     from the environment variable $SHELLOPTS if we are running in
//     privileged or restricted mode or if the shell is running setuid. */
//#if defined (RESTRICTED_SHELL)
//  initialize_shell_options (privileged_mode||restricted||running_setuid);
//#else
//  initialize_shell_options (privileged_mode||running_setuid);
//#endif
//}
