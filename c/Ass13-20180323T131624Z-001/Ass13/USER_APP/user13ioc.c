#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include"mygioctl.h"


int main()
{
	int fd,ret,buffcount;
	char buff[50];
	printf("Enter the string to be written to kernel\n");
	gets(buff);
	fd=open("/dev/muldevice3",O_RDWR);
	if (fd<0){
		perror("File muldevice3 opening failed\n");
		exit(0);
	}
	ret=write(fd,buff,strlen(buff));
	printf("Written %d bytes\n", ret);
	ioctl(fd,BUF_CNT,&buffcount);
	//sleep(5);
	printf("The buffercount is %d bytes\n", buffcount);
	ioctl(fd,BUF_DISP);
	ioctl(fd,BUF_CLR);
	ioctl(fd,BUF_DISP);
	close(fd);
	return 0;
}
