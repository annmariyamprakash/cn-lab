#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    socklen_t addr_size = sizeof(server_addr);

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    printf("Connected to server...\n");

    while (1) {
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, addr_size);
        if (strcmp(buffer, "exit") == 0) break;

        memset(buffer, 0, BUFFER_SIZE);
        recvfrom(client_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, &addr_size);
        buffer[strcspn(buffer, "\n")] = 0;

        printf("Server: %s\n", buffer);
        if (strcmp(buffer, "exit") == 0) break;
    }

    close(client_socket);
    return 0;
}
