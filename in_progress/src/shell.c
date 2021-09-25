#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	int		fd;
	int		pipe_fd[2];
	int		file_fd;
	char	buffer[1024];

	if (parse_env(&envp))
		return(1);
	pipe(pipe_fd);
	fd = fork();
	memset(buffer, '\0', 1024);
	if (fd == 0)
	{
		//if > stdout
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		shell_execve(argv[1], argv + 1, envp);
	}
	else if (fd > 0)
	{
		//if >
		close(pipe_fd[1]);
		file_fd = open("./sample", O_WRONLY | O_CREAT | O_TRUNC); //if >> open( , , O_APPEND);
		read(pipe_fd[0], buffer, 1023);
		write(file_fd, buffer, 1023);
		close(file_fd);
		close(pipe_fd[0]);
		wait(NULL);
	}
	else
		;
//	set_signal();
//	while(42)
//	{
//		line = readline();
//		if (readline == NULL)
//			exit();
//	}
}
