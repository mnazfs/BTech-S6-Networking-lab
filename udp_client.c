#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define port 9001
#define BUF 256
#define IP "127.0.0.1"

int main()
{
	int client_socket;
	struct sockaddr_in server_addr;
	socklen_t addr_size;
	char buffer[BUF];
	
	client_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(client_socket<0)
		perror("ERROR opening socket");
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=inet_addr(IP);
	
	addr_size=sizeof(server_addr);
	
	printf("Enter a message: ");
	fgets(buffer,BUF,stdin);
	sendto(client_socket,buffer,sizeof(buffer),0,(struct sockaddr*)&server_addr,addr_size);
	
	printf("Server echoed %s\n",buffer);
	
	close(client_socket);
	
	return 0;
}
		
		

