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
	printf("Enter the string to be written to kernel\n");
	gets(buff);
	fd=open("/dev/muldevice2",O_WRONLY);
	if (fd<0){
		perror("File muldevice2 opening failed\n");
		exit(0);
	}
	ret=write(fd,buff,strlen(buff));
	printf("Written %d bytes\n", ret);
	close(fd);
	return 0;
}
