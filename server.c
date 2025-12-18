#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define NUM_PHILOSOPHERS 5

int forks[NUM_PHILOSOPHERS] = {1, 1, 1, 1, 1}; // 1 = available

int leftFork(int id) { return id; }
int rightFork(int id) { return (id + 1) % NUM_PHILOSOPHERS; }

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Server running. Waiting for philosophers...\n");

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (new_socket < 0) continue;

        memset(buffer, 0, sizeof(buffer));
        read(new_socket, buffer, sizeof(buffer));

        int id;
        char action[16];
        sscanf(buffer, "%d %s", &id, action);

        if (strcmp(action, "REQUEST") == 0) {
            int left = leftFork(id);
            int right = rightFork(id);

            if (forks[left] && forks[right]) {
                forks[left] = forks[right] = 0;
                sprintf(buffer, "GRANTED");
            } else {
                sprintf(buffer, "DENIED");
            }
        } else if (strcmp(action, "RELEASE") == 0) {
            forks[leftFork(id)] = forks[rightFork(id)] = 1;
            sprintf(buffer, "RELEASED");
        }

        send(new_socket, buffer, strlen(buffer), 0);
        close(new_socket);
    }

    return 0;
}

