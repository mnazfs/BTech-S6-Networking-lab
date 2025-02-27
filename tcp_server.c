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
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0)
	{
		perror("ERROR in opening socket");
	}
	
	struct sockaddr_in server_addr, client_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(server_socket,(struct sockaddr*) &server_addr, sizeof(server_addr));
	
	listen(server_socket, 5);
	
	int client_socket = accept(server_socket, NULL, NULL);
	
	char buffer[256], temp;
	bzero(buffer,256);
	int re = read(client_socket,buffer,255);
	printf("\nThe message recieved : %s",buffer);
	
	int len = strlen(buffer);
	
	for (int i = 0; i < len/2; i++)  
    {  
        temp = buffer[i];  
        buffer[i] = buffer[len - i - 1];  
        buffer[len - i - 1] = temp;  
    }
    
	printf("\nThe reversed string : %s\n",buffer);
	
	int wr = write(client_socket,buffer, sizeof(buffer));
	
	close(server_socket);
	
	return 0;
}
