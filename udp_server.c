#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define port 9001
#define BUF 256

int main()
{
	int server_socket;
	struct sockaddr_in server_addr,client_addr;
	char buffer[BUF];
	server_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(server_socket<0)
		perror("ERROR opening socket");
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=INADDR_ANY;
	
	if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
		perror("ERROR binding to server");
		
	int addr_size=sizeof(client_addr);
	memset(buffer,0,BUF);
	int bytes_recieved=recvfrom(server_socket,buffer,BUF,0,(struct sockaddr*)&client_addr,&addr_size);
	printf("Recieved message: %s\n",buffer);
	sendto(server_socket,buffer,bytes_recieved,0,(struct sockaddr*)&client_addr,addr_size);
	
	close(server_socket);
	
	return 0;

}
	
