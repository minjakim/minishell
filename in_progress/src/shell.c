#include "../includes/minishell.h"

t_command	*make_cmd(void)
{
	t_command	*cmd1;

	cmd1 = malloc(sizeof(t_command));
	if (!cmd1)
		exit(1);
	cmd1->argv = malloc(sizeof(char *) * 3);
	if (!cmd1->argv)
		exit(1);
	cmd1->argv[0] = strdup("ls");
	cmd1->argv[1] = strdup("..");
	cmd1->argv[2] = NULL;
	cmd1->stream_out = 1;
	cmd1->stream_in = 0;
	cmd1->pipe = 0;
	cmd1->next = NULL;
	return (cmd1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*cmd_list;

	cmd_list = make_cmd();
	(void)&argc;
	(void)argv;
	if (parse_env(&envp))
		return(1);
	//parse_argv(); to NULL
	//signal setting
	//parse_prompt;
	//run_command();
	//check redirection with argv[1]
	shell_execve(cmd_list->argv[0], cmd_list->argv, envp);
	//redirect(argv, envp);
//	set_signal();
//	while(42)
//	{
//		line = readline();
//		if (readline == NULL)
//			exit();
//	}
}
