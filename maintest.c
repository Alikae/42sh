
#include "fcntl.h"
int main()
{
	int fd = open("/dev/null", O_RDONLY);
	printf("%i \n", fd);
	int pid = fork();
	if (!pid)
	{
		close(fd);
		int fd2 = open("/dev/random", O_RDONLY);
		printf("%i\n", fd2);
	}
}
