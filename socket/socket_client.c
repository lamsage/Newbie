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
	if(inet_pton(AF_INET, "127.0.0.1", &hostaddr.sin_addr) <= 0){
		printf("inet_pton error for %s", "127.0.0.1");
		exit(0);
	}
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(connect(listen_sock, (struct sockaddr *)&hostaddr, sizeof(hostaddr))< 0)
	{
		//syslog(LOG_ERR, "%s:%d", _FILE_, _LINE_);
		printf("2\n");
		exit(1);
	}
	char *msg = "hello \nworld";
	int i;
	i = send(listen_sock, msg, 1, 0);
	printf("%d\n", i);
	while(1)
	{
	}
	close(listen_sock);
}
