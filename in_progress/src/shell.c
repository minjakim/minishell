#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	//char *line;

	(void)&argc;
	if (parse_env(&envp))
		return(1);
	//parse_argv(); to NULL
	//signal setting
	//parse_prompt;
	//run_command();
	//check redirection with argv[1]
	redirect(argv, envp);
//	set_signal();
//	while(42)
//	{
//		line = readline();
//		if (readline == NULL)
//			exit();
//	}
}
