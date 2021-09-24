#include "../includes/minishell.h"



int	main(int argc, char *argv[], char *envp[])
{
	char *line;

	parsing_env();
	printf("%s\n", envp[0]);
	*envp[0]='a';
	printf("%s\n", envp[0]);
	free(*envp);
//	set_signal();
//	while(42)
//	{
//		line = readline();
//		if (readline == NULL)
//			exit();
//	}
}
