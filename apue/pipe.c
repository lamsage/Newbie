#include "apue.h"

int main(void){
	int fd[2];
	if(pipe(fd) < 0)
		err_sys("error pipe\n");
	close(fd[0]);
	write(fd[1], "hello", 5);
	close(fd[1]);
	printf("finish\n");
	return 0;

}
