#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	struct stat statbuf;
	int		stat_value;

	if ((stat_value = stat(argv[1],  &statbuf)))
		printf("error\n");
	printf("st_size %ld\n", statbuf.st_size);
}
