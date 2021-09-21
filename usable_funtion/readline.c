//test readline library
//
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*dest;
	
	while (1)
	{
		dest = readline("snpark> ");
		printf("%s\n", dest);
		if (dest)
			free(dest);
	}
	return (0);
}


