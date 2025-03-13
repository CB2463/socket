#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = "HELLO, SERVER!";

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
	    perror("FAIL MAKING SOCKET");
	    exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
	    perror("FAIL SERVER CONNECTION");
	    exit(1);
    }

    write(client_fd, buffer, strlen(buffer));

    memset(buffer, 0, BUFFER_SIZE);
    read(client_fd, buffer, BUFFER_SIZE);
    printf("SERVER ACCPET: %s\n", buffer);

    close(client_fd);

    return 0;
}
