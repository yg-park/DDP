#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
	int ret;
	ret=mknod("/dev/devfile", 0777 | S_IFCHR, (240 << 8) | 1);
	if(ret<0)
	{
		perror("mknod()");
		return -ret;
	}



	return 0;
}
