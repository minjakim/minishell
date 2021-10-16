/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:13:44 by snpark            #+#    #+#             */
/*   Updated: 2021/10/16 11:46:04 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

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

int
	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_shell		mini;

	(void)&argc;
	(void)argv;
	if (parse_env(&envp))
		return(1);
	initialize(&mini);
	while (1)
	{
		line = readline(PROMPT);
		mini.cmd_handle = mini.cmd_list;
		while (mini.cmd_handle != NULL)
		{
			redirect(mini.cmd_handle);
			mini.cmd_handle = mini.cmd_handle->next;
		}
		/*execute cmd*/
		mini.cmd_handle = mini.cmd_list;
		while (mini.cmd_handle != NULL)
		{
			/*$sign 해석을 이곳에서 해야함*/
			shell_execve(*mini.cmd_handle, envp);
			mini.cmd_handle = mini.cmd_handle->next;
		}
	}
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
