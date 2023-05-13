#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int server_socket, client_socket, read_size;
    struct sockaddr_in server_address, client_address;
    char client_message[2000];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(5000);

    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    listen(server_socket, 1);

    puts("Waiting for incoming connections...");

    while (1) {
        socklen_t client_address_len = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);

        char client_address_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_address.sin_addr, client_address_str, INET_ADDRSTRLEN);
        printf("Connection from %s\n", client_address_str);

        memset(client_message, 0, sizeof(client_message));
        read_size = recv(client_socket, client_message, 2000, 0);
        printf("Received message from client: %s\n", client_message);

        for (int i = 0; i < read_size; i++) {
            if (client_message[i] >= 'A' && client_message[i] <= 'Z') {
                client_message[i] += 'a' - 'A';
            } else if (client_message[i] >= 'a' && client_message[i] <= 'z') {
                client_message[i] -= 'a' - 'A';
            }
        }

        send(client_socket, client_message, strlen(client_message), 0);
        printf("Sent message to client: %s\n", client_message);

        close(client_socket);
    }

    return 0;
}




/*
-----------------------------------
Algorithm: 
	Create a TCP socket using `socket()` function.
	Initialize the socket address structure with server IP address and port number using `bind()` function.
	Listen for incoming connections using `listen()` function.
	Accept incoming connection using `accept()` function and get client's IP address.
	Receive data from the client using `recv()` function.
	Convert the data received from the client to reverse case.
	Send the reverse case data back to the client using `send()` function.
	Close the connection using `close()` function
*/
