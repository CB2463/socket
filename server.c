#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
	    perror("FAil MAKING SOCKET");
	    exit(1);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
	    perror("FAIL BINDING");
	    exit(1);
    }

    if (listen(server_fd, 5) == -1) {
	    perror("FAIL LISTENING");
	    exit(1);
    }

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd == -1) {
	    perror("FAIL client connection");
	    exit(1);
    }

    printf("CLIENT connected: %s\n", inet_ntoa(client_addr.sin_addr));

    memset(buffer, 0, BUFFER_SIZE);
    read(client_fd, buffer, BUFFER_SIZE);
    printf("RCV MESSAGE: %s\n", buffer);

    write(client_fd, buffer, strlen(buffer));
    close(client_fd);
    close(server_fd);

    return 0;
}

