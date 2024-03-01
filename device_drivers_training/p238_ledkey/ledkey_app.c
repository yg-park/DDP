#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#pragma GCC diagnostic ignored "-Wunused-result"
int main(int argc, char *argv[])
{
	char buff;
	int i;
	int ledkeyfd;
	int key_data,key_data_old=0;
	unsigned long val=0;
	if(argc < 2)
	{
		printf("USAGE : %s ledVal[0x00~0xff]\n",argv[0]);
		return 1;
	}
	val = strtoul(argv[1],NULL,16);
	if(val<0 || 0xff<val)
	{
		printf("Usage : %s ledValue[0x00~0xff]\n",argv[0]);
		return 2;
	}
	ledkeyfd = open("/dev/ledkey", O_RDWR | O_NONBLOCK);
	if(ledkeyfd < 0)
	{
		perror("open()");
		return 1;
	}
	buff = (char)val;
	write(ledkeyfd, &buff, sizeof(buff));
	do {
		usleep(100000);  //100MSec
//		key_data = syscall(__NR_mysyscall,val);
		read(ledkeyfd, &buff, sizeof(buff));
		key_data = buff;
		if(key_data != key_data_old)
		{
			key_data_old = key_data;
			if(key_data)
			{
				write(ledkeyfd, &buff, sizeof(buff));
				puts("0:1:2:3:4:5:6:7");
				for(i=0;i<8;i++)
				{
					if(key_data & (0x01 << i))
						putchar('O');
					else
						putchar('X');
					if(i != 7 )
						putchar(':');
					else
						putchar('\n');
				}
				putchar('\n');
			}
			if(key_data == 0x80)
				break;
		}
	}while(1);
	printf("mysyscall return value = %#04x\n",key_data);
	return 0;
}
