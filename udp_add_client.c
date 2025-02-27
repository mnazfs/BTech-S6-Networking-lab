#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define port 9002
#define BUF 256
#define IP "127.0.0.1"

int main()
{
	int client_socket;
	struct sockaddr_in server_addr;
	socklen_t addr_size;
	int num1,num2,sum;
	
	client_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(client_socket<0)
		perror("ERROR opening socket");
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=inet_addr(IP);
	
	addr_size=sizeof(server_addr);
	
	printf("Enter num1: ");
	scanf("%d",&num1);
	sendto(client_socket,&num1,sizeof(num1),0,(struct sockaddr*)&server_addr,addr_size);
	
	printf("Enter num2: ");
	scanf("%d",&num2);
	sendto(client_socket,&num2,sizeof(num2),0,(struct sockaddr*)&server_addr,addr_size);
	
	int bytes_recieved=recvfrom(client_socket,&sum,sizeof(sum),0,(struct sockaddr*)&server_addr,&addr_size);
	printf("Server echoed %d\n",sum);
	
	close(client_socket);
	
	return 0;
}
		
		

