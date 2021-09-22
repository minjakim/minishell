#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

//stat()과 차이는 첫번째 인자가 경로에서 fd로 변함 

int	main(int argc, char **argv)
{
	struct stat statbuf;
	int		stat_value;
	int		fd;


	fd = open(argv[1], O_RDONLY);
	if ((stat_value = fstat(fd,  &statbuf)))
		printf("error\n");
	printf("st_size %ld\n", statbuf.st_size);
	close(fd);
}
