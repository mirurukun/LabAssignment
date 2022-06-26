#include <stdio.h>
#include <string.h>     //strlen
#include <sys/socket.h>
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>     //write

int main(int argc , char *argv[])
{
        int socket_desc , new_socket , c;
        struct sockaddr_in server , client;
        char  client_message[1000];
        char buffer[1024] = { 0 };
        char message[sizeof(buffer)];


        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( 8888 );

        //Bind
        if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("bind failed");
                return 1;
        }
        puts("bind done");

        //Listen
        listen(socket_desc , 3);

        //Accept and incoming connection
        puts("Waiting for incoming connections...");
        c = sizeof(struct sockaddr_in);

        while(1)
        {
               new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c); 
                puts("Connection accepted\n");

                while(1){
                //Message from Client
                if( recv(new_socket, client_message , 1000 , 0) < 0)
                    {
                      puts("recv failed");
                    }


                 printf("Client :");
                 puts(client_message);

                //Reply to the client
                printf("Server : ");
                scanf("%s", message);
                printf("\n");
                write(new_socket , message , strlen(message));
                }
        }

        if (new_socket<0)
        {
                perror("accept failed");
                return 1;
        }

        return 0;
}
