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
	char buff[50],buff2[50];
	printf("Enter the string to be written to kernel\n");
	gets(buff);
	fd=open("/dev/muldevice3",O_RDWR);
	if (fd<0){
		perror("File muldevice3 opening failed\n");
		exit(0);
	}
	ret=write(fd,buff,strlen(buff));
	printf("Written %d bytes\n", ret);
	memset(buff2,'\0',50);
	ret=read(fd,buff2,sizeof(buff2));
	printf("Consumer read : %s of %d bytes\n", buff2, ret);
	close(fd);
	return 0;
}
