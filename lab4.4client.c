#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <string.h>


int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
    char buffer[1024] = { 0 };
    char message[sizeof(buffer)];
	char server_reply[1000];

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	server.sin_addr.s_addr = inet_addr("192.168.202.5"); //Please enter the ip address of your Server VM
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected \n");

    while(1){

	//Send some data
	printf("Client  : ");
        scanf(" %s", message);

	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}

    //Receive a reply from the server
	if( recv(socket_desc, server_reply , 1000 , 0) < 0)
	{
		puts("recv failed");
	}
	printf("Server : ");
	puts(server_reply);
        printf("\n");

        }
        close(socket_desc);
	return 0;
}
