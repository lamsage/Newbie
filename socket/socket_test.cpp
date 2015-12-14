#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<syslog.h>
#include<errno.h>
#define MAX_LISTEN_NUM 5
#define SEND_BUF_SIZE 100
#define RECV_BUF_SIZE 100
#define LISTEN_PORT 8080
int main()
{
	int listen_sock = 0;
	int app_sock = 0;
	struct sockaddr_in hostaddr;
	struct sockaddr_in clientaddr;
	socklen_t socklen = sizeof(clientaddr);
	char sendbuf[SEND_BUF_SIZE] = {0};
	char recvbuf[RECV_BUF_SIZE] = {0};
	int sendlen = 0;
	int recvlen = 0;
	int retlen = 0;
	int leftlen = 0;
	char *ptr = NULL;
	memset((void * )&hostaddr, 0, sizeof(hostaddr));
	memset((void * )&clientaddr, 0, sizeof(clientaddr));
	hostaddr.sin_family = AF_INET;
	hostaddr.sin_port = htons(LISTEN_PORT);
	hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock < 0)
	{
		//syslog(LOG_ERR, "%s:%d", _FILE_, _LINE_);
		printf("1\n");
		exit(1);
	}
	if(bind(listen_sock, (struct sockaddr *)&hostaddr, sizeof(hostaddr))< 0)
	{
		//syslog(LOG_ERR, "%s:%d", _FILE_, _LINE_);
		printf("2\n");
		exit(1);
	}
	if(listen(listen_sock, MAX_LISTEN_NUM) < 0)
	{
		//syslog(LOG_ERR, "%s:%d", _FILE_, _LINE_);
		printf("3\n");
		exit(1);
	}
	while(1)
	{
		app_sock = accept(listen_sock, (struct sockaddr*) &clientaddr, &socklen);
		if(app_sock < 0)
		{
			//syslog(LOG_ERR, "%s:%d", _FILE_, _LINE_);
			printf("4\n");
			exit(1);
		}
		recvlen = 0;
		retlen = 0;
		ptr = recvbuf;
		leftlen = RECV_BUF_SIZE -1;
		{
			retlen = recv(app_sock, ptr, leftlen, 0);
			if(retlen < 0)
			{
				if(errno == EINTR)
					retlen = 0;
				else 
					exit(1);
			}
			printf("receive data %d\n", retlen);
			recvlen += retlen;
			leftlen -= retlen;
			ptr += retlen;
		}
		printf("receive data is : %s\n", recvbuf);
		close(app_sock);
	}
	close(listen_sock);
}
