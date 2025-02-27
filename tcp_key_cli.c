#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

#define port 9001

int main(){
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	int key;
	char buffer[256];
	if(sockfd<0){
		perror("An error occured during socket connection\n");
	}
	
	struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=INADDR_ANY;
	
	int connection_status=connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(connection_status<0){
		perror("Error establishing connection\n");
	}
	
	printf("Enter your key\n");
	scanf("%d",&key);
	
	int wr=write(sockfd,&key,sizeof(key));
	if(wr<0){
		perror("Error\n");
	}
	
	int re=read(sockfd,buffer,sizeof(buffer));
	if(re<0){
		perror("Error\n");
	}
	
	printf("Value:%s\n",buffer);
	close(sockfd);
	
	
	
}
	


