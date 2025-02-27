#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define port 9001

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("ERROR opening socket");
	}	
	
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	int connection_status = connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
	if (connection_status < 0)
	{
		perror("ERROR connecting");
	}
	
	printf("\nEnter a string : ");
	char str[256];
	bzero(str,256);
	scanf("%s",str);
	
	int wr = write(sockfd,str,strlen(str));
	if (wr < 0)
	{
		perror("ERROR writing to socket");
	}
	
	int re = read(sockfd, str, 255);
	if (re < 0)
	{
		perror("ERROR reading from socket");
	}
	
	printf("The reversed string : %s\n",str);

	close(sockfd);
	
	return 0;
}
