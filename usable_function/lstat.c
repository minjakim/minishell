#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

//
//파일이 심볼릭 링크면 그 심볼릭 링크 파일의 정보를 참조함
//심볼릭 링크가 가리키는 파일이 아니라

int	main(int argc, char **argv)
{
	struct stat statbuf;
	int		stat_value;


	if ((stat_value = lstat(argv[1], &statbuf)))
		printf("error\n");
	printf("off_t	%li\n", statbuf.st_size);
}
