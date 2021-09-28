#include "../includes/minishell.h"

void	stdout_to_file(char **argv, char **envp, int flag)
{
	int		fd;
	int		file_fd;

	file_fd = open("sample", flag, 0b111101101);
	fd = fork();
	if (fd == 0)
	{
		dup2(file_fd, 1);
		shell_execve(argv[2], argv + 2, envp);
	}
	else if (fd > 0)
	{
		close(file_fd);
		wait(NULL);
	}
	else
	{
		write(2, strerror(errno), strlen(strerror(errno)));
		exit(errno);
	}
}

void	file_to_stdin(char **argv, char **envp)
{
	int		read_fd;
	int		fork_fd;

	read_fd = open("sample", O_RDONLY); 
	fork_fd = fork();
	if (fork_fd > 0)
	{
		close(read_fd);
		wait(NULL);
	}
	else if (fork_fd == 0)
	{
		dup2(read_fd, 0);
		shell_execve(argv[2], argv + 2, envp);
	}
	else
		;
}

void	stdin_to_stdin(char **argv, char **envp)
{
	int		pipe_fd[2];
	int		fork_fd;
	char	buffer[1024];
	int		read_len;

	//read from stdin
	memset(buffer, '\0', 1024);
	if (pipe(pipe_fd))
		;//error
	while ((read_len = read(0, buffer, 1024)))
	{
		if (read_len == -1)
		{
			if (errno == EINTR)//read intrupped by signal
				continue;
			//error
		}
		if (strcmp(buffer, "END\n") == 0)
			break;
		write(pipe_fd[1], buffer, read_len);
		memset(buffer, '\0', 1024);
	}
	fork_fd = fork();
	if(fork_fd > 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		wait(NULL);
	}
	else if (fork_fd == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		shell_execve(argv[2], argv + 2, envp);
	}
	else
		;
}
void	stdout_to_stdin()
{

}

int	redirect(char **argv, char **envp)
{
	int		pipe_fd[2];


	pipe(pipe_fd);
	if (*argv[1] == '>')
	{
		if (argv[1][1] == '>')
			stdout_to_file(argv, envp, O_WRONLY | O_CREAT | O_APPEND);
		else
			stdout_to_file(argv, envp, O_WRONLY | O_CREAT | O_TRUNC);
	}
	else if (*argv[1] == '<')
	{
		if (argv[1][1] == '<')
			stdin_to_stdin(argv, envp);
		else
			file_to_stdin(argv, envp);
	}
	if (*argv[1] == '|')
		;//stdout_to_stdin();
	return (0);
}
