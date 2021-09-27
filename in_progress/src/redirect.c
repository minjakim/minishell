#include "../includes/minishell.h"

void	stdout_to_file(char **argv, char **envp, int pipe_fd[2], int flag)
{
	int		fd;
	int		file_fd;
	char	buffer[1024];

	fd = fork();
	memset(buffer, '\0', 1024);
	if (fd == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		shell_execve(argv[2], argv + 2, envp);
	}
	else if (fd > 0)
	{
		close(pipe_fd[1]);
		file_fd = open("sample", flag, 0b111101101);
		read(pipe_fd[0], buffer, 1023);
		write(file_fd, buffer, 1023);
		close(file_fd);
		close(pipe_fd[0]);
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
	if (fork_fd > 0)
	{
		close(read_fd);
		wait(NULL);
	}
	else if (fork_fd == 0)
	{
		close(pipe_fd[1]);
		dup2(read_fd, 0);
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
			stdout_to_file(argv, envp, pipe_fd, O_WRONLY | O_CREAT | O_APPEND);
		else
			stdout_to_file(argv, envp, pipe_fd, O_WRONLY | O_CREAT | O_TRUNC);
	}
	else if (*argv[1] == '<')
	{
		if (argv[1][1] == '<')
			;
//		{
//			while (buffer =="end")
//			{
//				read(buffer);
//				write(pipe_fd[1], buffer)
//				free(buffer);
//			}
//			child
//			{
//				dup2(pipe_fd[0], 0);
//				execve("cat");
//			}
//			i_to_o();
//		}
		else
			file_to_stdin(argv, envp, pipe_fd);
	}
	if (*argv[1] == '|')
		;//stdout_to_stdin();
//	else if (*argv[1] == '<')
//	{
//		file_fd = open("./sample", O_RDONLY);
//		read(file_fd, buffer, 1023);
//		write(pipe_fd[1], buffer, 1023);
//		fd = fork();
//		if (fd == 0)
//		{
//			close(pipe_fd[0]);
//			dup2(pipe_fd[0], 0);
//			shell_execve(argv[2], argv + 1, envp);
//		}
//		else if (fd > 0)
//		{
//			close(pipe_fd[0]);
//			close(pipe_fd[1]);
//			close(file_fd);
//			wait(NULL);
//		}
//		else
//			;//error
//	}
//	else if (*argv[1] == '<<')
//	{
//		while ()
//		{
//			readline("		>");
//		}
//	}
//	else if (*argv[1] == '|')
//		;
//	else // no redirection
//	{
//		close(pipe_fd[0]);
//		close(pipe_fd[1]);
//		fd = fork();
//		if (fd == 0)
//			shell_execve(argv, argv + 1, envp);
//		else if (fd > 0)
//			wait(NULL);
//		else
//			exit(errno);//error
//	}
	return (0);
}
