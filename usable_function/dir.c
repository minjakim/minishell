/*
** opendir, raaddir, closedir
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	DIR	*dir_stream_pointer;
	struct dirent *dirinfo;

	dir_stream_pointer = opendir(argv[1]);
	if (dir_stream_pointer == NULL)
		return (1);	
	while ((dirinfo = readdir(dir_stream_pointer)))//정적할당되어있음
		printf("inode nuber %ld, off_t %ld, length of record %u, type of file %u, filename %s\n", dirinfo->d_ino, dirinfo->d_off, dirinfo->d_reclen, dirinfo->d_type, dirinfo->d_name);
	if (closedir(dir_stream_pointer) != 0)
		return (1);
	return (0);
}
