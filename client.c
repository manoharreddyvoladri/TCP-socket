#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int client_socket, read_size;
    struct sockaddr_in server_address;
    char server_response[2000], message[2000];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(5000);

    connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    printf("Enter a message: ");
    fgets(message, 2000, stdin);
    message[strcspn(message, "\n")] = 0;

    send(client_socket, message, strlen(message), 0);

    memset(server_response, 0, sizeof(server_response));
    read_size = recv(client_socket, server_response, 2000, 0);

    printf("Server's response: %s\n", server_response);

    close(client_socket);

    return 0;
}
/*
------------------------
Algorithm: 

	Create a TCP socket using `socket()` function.
	Initialize the socket address structure with server IP address and port number using `connect()` function.
	Prompt user to enter message.
	Send the message to server using `send()` function.
	Receive the reversed message from server using `recv()` function.
	Display the reversed message on the console.
	Close the socket using `close()` function.

*/
