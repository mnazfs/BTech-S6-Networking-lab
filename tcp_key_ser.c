#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

#define port 9001

struct data{
	int key;
	char value[10];
}pair[10];

int main()
{
	pair[0]=(struct data){1,"Sufaida"};
	pair[1]=(struct data){2,"Naseef"};
	pair[2]=(struct data){3,"Asif"};
	pair[3]=(struct data){4,"Saleh"};
	pair[4]=(struct data){5,"Sabir"};
	
	int server_socket=socket(AF_INET,SOCK_STREAM,0);
	if(server_socket<0){
		printf("Error in opening the socket\n");
	}
	
	struct sockaddr_in server_addr, client_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=INADDR_ANY;
	
	
	bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	listen(server_socket,5);
	
	int client_socket=accept(server_socket,NULL,NULL);
	
	char buffer[256];
	FILE * fp;
	int k;
	bzero(buffer,256);
	
	int re=read(client_socket,&k,sizeof(k));
	printf("Key:%d\n",k);
	
	for(int i=0;i<10;i++)
	{
		if((pair[i].key)==k){
			int wr=write(client_socket,pair[i].value,sizeof(pair[i].value));
			printf("Value: %s\n",pair[i].value);
			break;
		}
	}
	
	close(server_socket);
	return 0;
}
