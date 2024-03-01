#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <string.h>

#define DEVICE_FILENAME "/dev/ledkey_dev"

int main(int argc, char *argv[])
{
	int dev;
	char buff;
	int ret;
	int num = 1;
	struct pollfd Events[2];
	char keyStr[80];

    if(argc != 2)
    {
        printf("Usage : %s [led_data(0x00~0xff)]\n",argv[0]);
        return 1;
    }
    buff = (char)strtoul(argv[1],NULL,16);
    if((buff < 0x00) || (0xff < buff))
    {
        printf("Usage : %s [led_data(0x00~0xff)]\n",argv[0]);
        return 2;
    }

//  dev = open(DEVICE_FILENAME, O_RDWR | O_NONBLOCK);
  	dev = open(DEVICE_FILENAME, O_RDWR );
	if(dev < 0)
	{
		perror("open");
		return 2;
	}
	write(dev,&buff,sizeof(buff));

	fflush(stdin);
	memset( Events, 0, sizeof(Events));
  	Events[0].fd = fileno(stdin);
  	Events[0].events = POLLIN;
	Events[1].fd = dev;
	Events[1].events = POLLIN;
	while(1)
	{
		ret = poll(Events, 2, 2000);
		if(ret<0)
		{
			perror("poll");
			exit(1);
		}
		else if(ret==0)
		{
  			printf("poll time out : %d Sec\n",2*num++);
			continue;
		}
		if(Events[0].revents & POLLIN)  //stdin
		{
			fgets(keyStr,sizeof(keyStr),stdin);
			if(keyStr[0] == 'q')
				break;
			keyStr[strlen(keyStr)-1] = '\0';  //'\n' clear
			printf("STDIN : %s\n",keyStr);
			buff = (char)strtoul(keyStr, 0, 16);
//			buff = (char)atoi(keyStr);
			write(dev,&buff,sizeof(buff));
		}
		else if(Events[1].revents & POLLIN) //ledkey
		{
			ret = read(dev,&buff,sizeof(buff));
			printf("key_no : %d\n",buff);
			if(buff == 8)
				break;
			buff = 1 << buff-1;
			write(dev,&buff,sizeof(buff));
		}
	}
	close(dev);
	return 0;
}
