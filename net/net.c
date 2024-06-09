#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

#include "net.h"
#include "../functions/frunner.h"

void send_buffer(unsigned char* buffer, unsigned int size) {
    struct sockaddr_in client;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("Failed to create socket; %d", errno);
        return;
    }
    memset(&client, 0, sizeof(struct sockaddr_in));

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(source_ip);
    client.sin_port = htons(source_port);

    if (connect(fd, (struct sockaddr*)&client, sizeof(struct sockaddr_in)) != 0) {
        printf("Failed to connect; %d", errno);
        return;
    }

    write(fd, buffer, size);
    
    close(fd);
}

struct fbuffer read_buffer() {
    struct sockaddr_in server;

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("Failed to create socket; %d", errno);
        goto exit;
    }
    memset(&server, 0, sizeof(struct sockaddr_in));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(source_port);

    if ((bind(fd, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) != 0)) {
        printf("Failed to bind socket; %d", errno);
        goto exit;
    }

    if (listen(fd, 1) != 0) {
        printf("Failed to listen; %d", errno);
        goto exit;
    }

    unsigned int length;
    int client_fd = accept(fd, (struct sockaddr*)&server, &length);
    if (client_fd < 0) {
        printf("Failed to accept client; %d", errno);
        goto exit;
    }

    unsigned char read_buffer[buffer_size];
    memset(&read_buffer, 0xC3, buffer_size);

    read(client_fd, read_buffer, buffer_size);
    close(client_fd);

exit:
    close(fd);

    return get_function(read_buffer);
}
