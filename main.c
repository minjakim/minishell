/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/10/19 20:31:34 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include <string.h>

int
	__sflush(FILE *fp)
{
	unsigned char	*p;
	int				n;
	int				t;

	t = fp->_flags;
	p = fp->_bf._base;
	if ((!(t & __SWR)) || !p)
		return (0);
	n = fp->_p - p;
	fp->_p = p;
	fp->_w = 0;
	if (!(t & (__SLBF | __SNBF)))
		fp->_w = fp->_bf._size;
	while (n > 0)
	{
		t = (*fp->_write)(fp->_cookie, (char *)p, n);
		if (t <= 0)
		{
			fp->_flags |= __SERR;
			return (EOF);
		}
		n -= t;
		p += t;
	}
	return (0);
}

int
	ft_fflush(FILE *fp)
{
	if (fp == NULL)
		return (0);
	if ((fp->_flags & (__SWR | __SRW)) == 0)
	{
		errno = EBADF;
		return (EOF);
	}
	return (__sflush(fp));
}

static void
	get_cursor_position(t_curses *curses)
{
	int		i;
	char	buf[255];

	write(1, "\033[6n", 4);
	i = read(0, buf, 254);
	buf[i] = '\0';
	i = 1;
	while (!((unsigned)buf[i] - 48 < 10))
		++i;
	while (((unsigned)buf[i] - 48) < 10)
		curses->row = (curses->row << 1) + (curses->row << 3) + (buf[i++] - 48);
}

static int
	putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

static void
	exit_eof_test(t_shell *mini)
{
	mini->config.current.c_lflag &= ~ICANON;
	mini->config.current.c_lflag &= ~ECHO;
	mini->config.current.c_cc[VMIN] = 1;
	mini->config.current.c_cc[VTIME] = 0;
	mini->curses.row = 0;
	mini->curses.column = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->config.current);
	get_cursor_position(&mini->curses);
	tputs(tgoto(mini->curses.move, mini->curses.column += sizeof(PROMPT) - 1, mini->curses.row -= 2), 1, putchar_tc);
	printf("exit\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->config.backup);
	exit(errno);
}

static void
	sig_handler(int signum)
{

	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

static void
	initialize(t_shell *mini)
{
	tgetent(NULL, "xterm");
	mini->curses.move = tgetstr("cm", NULL);
	tcgetattr(STDIN_FILENO, &mini->config.current);
	mini->config.backup = mini->config.current;
	mini->config.current.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &mini->config.current);
	signal(SIGINT, sig_handler);
	rl_catch_signals = 0;
}

static void
	excute_sub(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		exit_status;

	if (cmd->pipe.out != -1)
	{
		pipe(cmd->pipe.fd);
		cmd->pipe.out = cmd->pipe.fd[0];
		cmd->next->pipe.in = cmd->pipe.fd[1];
	}
	pid = fork();
	if (pid == 0)
	{
		if (cmd->pipe.out != -1)
			dup2(cmd->pipe.out, 1);
		if (cmd->pipe.in != -1)
			dup2(cmd->pipe.in, 0);
		//replace_env();
		redirect(cmd);
		shell_execve(*cmd, envp);
	}
	else if (pid > 0)
	{
		if (cmd->pipe.in != -1 && cmd->pipe.out == -1)/*마지막 파이프 커맨드*/
		{
			waitpid(pid, &exit_status, 0);/*파이프의 마지막 커맨드의 종료상태 반환*/
			while(wait(NULL) != -1)/*자식프로세스가 없을 때까지 대기*/
				;
		}
	}
}

static void
	excute_main(t_command *cmd, char **envp)
{
	int		exit_status;

	while (cmd)
	{
		if (cmd->pipe.in != -1 || cmd->pipe.out != -1)
			excute_sub(cmd, envp);
		else//main
		{
			//replace_env(); 환경변수 치환하는 함수
			redirect(cmd);
			shell_execve(*cmd, envp);
		}
		cmd = cmd->next;
		//if (flag == "&&" && exit_status == 1)
		//	exit();
		//if (flag == "||" && exit_status == 0)
		//	eixt();
	}
}

int
	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_shell		mini;
	char		last_state;
	t_command	*cmd_list;
	//t_hash	*export_list;export된 변수 관리용

	(void)&argc;
	(void)argv;
	if (parse_env(&envp))//export_list인자 추가
		return(1);
	initialize(&mini);
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*(int *)line == 1953069157 && line[5] == '\0')
		{
			printf("exit\n");
			tcsetattr(STDIN_FILENO, TCSANOW, &mini.config.backup);
			return (errno);
		}
		add_history(line);
		free(line);
		/*parseing?*/
		excute_main(cmd_list, envp);//export_list인자 추가
	}
	exit_eof_test(&mini);
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
