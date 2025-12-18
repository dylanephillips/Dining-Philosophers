#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"

void think(int id) {
    printf("Philosopher %d is thinking...\n", id);
    sleep(rand() % 3 + 1);
}

void eat(int id) {
    printf("Philosopher %d is eating!\n", id);
    sleep(rand() % 2 + 1);
}

int requestForks(int id) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    char msg[32], response[32];
    sprintf(msg, "%d REQUEST", id);
    send(sock, msg, strlen(msg), 0);
    read(sock, response, sizeof(response));
    close(sock);

    return strstr(response, "GRANTED") != NULL;
}

void releaseForks(int id) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    char msg[32];
    sprintf(msg, "%d RELEASE", id);
    send(sock, msg, strlen(msg), 0);
    close(sock);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s philosopher_id\n", argv[0]);
        return 1;
    }

    int id = atoi(argv[1]);
    srand(getpid());

    while (1) {
        think(id);

        if (requestForks(id)) {
            eat(id);
            releaseForks(id);
        } else {
            printf("Philosopher %d could not get forks, waiting...\n", id);
            sleep(1);
        }
    }
}

