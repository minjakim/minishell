#include "../includes/minishell.h"



int	main(int argc, char *argv[], char *envp[])
{
	char *line;

	if (parse_env(&envp))
		return(1);
	ft_execve(argc, argv, envp);
//	set_signal();
//	while(42)
//	{
//		line = readline();
//		if (readline == NULL)
//			exit();
//	}
}
