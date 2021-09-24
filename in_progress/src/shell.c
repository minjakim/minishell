#include "../includes/minishell.h"



int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	int		i;

	i = -1;
	while (envp[++i] != NULL)
		printf("%s\n", envp[i]);
	if (parse_env(&envp))
		return(1);
	printf("------------------------------------------");
	i = -1;
	while (envp[++i] != NULL)
		printf("%s\n", envp[i]);
//	set_signal();
//	while(42)
//	{
//		line = readline();
//		if (readline == NULL)
//			exit();
//	}
}
