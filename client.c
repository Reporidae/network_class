#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024
#define PORT 9000

int main(int argc, char **argv)
{
	int client_socket;
	
	struct sockaddr_in server_addr;

	char buff[BUFF_SIZE+5];
	
	//client socket generation
	client_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(-1 == client_socket)
	{
		printf("socket generation failure\n");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// request connection to server
	if(-1 == connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
	{
		printf("connection failure\n");
		exit(1);
	}

	while(1)
	{
		printf("Enter Message (type 'bye' to quit): ");
		fgets(buff, sizeof(buff), stdin);
		buff[strcspn(buff, "\n")] = 0;

		write(client_socket, buff, strlen(buff) + 1);
		
		if(strcmp(buff, "bye") == 0)
		{
			break;
		}

		read(client_socket, buff, BUFF_SIZE);
		printf("response from server: %s\n", buff);
	}

	// close socket
	close(client_socket);
	return 0;

}
