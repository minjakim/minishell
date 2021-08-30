#include <stdio.h>
#include <unistd.h>

int	env(char **envp)
{
	int	env_i;

	env_i = 0;
	while (envp[env_i])
		printf("%s\n", envp[env_i++]);
	return (0);
}

int	pwd()
{
	char cwd_buffer[4096];

	getcwd(cwd_buffer, 4096);
	printf("%s\n", cwd_buffer);
}

int	main(int argc, char **argv, char **envp)
{
}
