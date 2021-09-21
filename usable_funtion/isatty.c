#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int	main(void)
{
	int	fd;
	int	pid_return;

	fd = fork();
	printf("fd = %d is tty ? = %d\n", fd, isatty(fd));
	if (fd == 0)
		exit(0);
	else if (fd < 0)
		exit(1);
	else
		waitpid(-1, &pid_return, 0);
	return (0);
}
