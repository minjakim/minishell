#include "../includes/minishell.h"

void	o_to_i(char **argv, char **envp, int pipe_fd[2], int flag)
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

void	i_to_o()
{

}

void	pipe_o_to_i()
{
	
}

int	redirect(char **argv, char **envp)
{
	int		pipe_fd[2];
	//int		fd;
	////int		file_fd;


	pipe(pipe_fd);
	if (*argv[1] == '>')
	{
		if (argv[1][1] == '>')
			o_to_i(argv, envp, pipe_fd, O_WRONLY | O_CREAT | O_APPEND);
		else
			o_to_i(argv, envp, pipe_fd, O_WRONLY | O_CREAT | O_TRUNC);
	}
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
