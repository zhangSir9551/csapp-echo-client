# include "csapp.h"

int main(int argc, char **argv)
{
	int clientfd;	   // 客户端套接字描述符
	char *host, *port; // 服务器的主机名（或者IP）和端口号
	char buf[MAXLINE]; // 数据缓冲区
	rio_t rio;		   // Rio 的读缓冲区结构体，用于带缓冲的读取

	if (argc != 3) // 要求两个命令行参数：主机名和端口号
	{
		fprintf(stderr, "usage: %s <host> <port> \n", argv[0]);
		exit(0);
	}

	host = argv[1];
	port = argv[2];

	clientfd = Open_clientfd(host, port);
	Rio_readinitb(&rio, clientfd);

	while(Fgets(buf, MAXLINE, stdin) != NULL)
	{
		Rio_writen(clientfd, buf, strlen(buf));
		Rio_readlineb(&rio, buf, MAXLINE);
		Fputs(buf, stdout);
	}

	Close(clientfd);
	exit(0);
}