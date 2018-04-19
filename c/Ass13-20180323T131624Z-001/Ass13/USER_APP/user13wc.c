#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>

int main()
{
	int fd,ret;
	char buff[50];
	memset(buff,'\0',50);
	fd=open("/dev/muldevice2",O_RDONLY);
	if (fd<0){
		perror("Opening muldevice2 file failed\n");
		exit(0);
	}
	ret=read(fd,buff,sizeof(buff));
	printf("Consumer read : %s of %d bytes\n", buff, ret);
	close(fd);
	return 0;
}
