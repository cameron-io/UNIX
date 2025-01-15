#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include "server.h"

char
*make_payload() {
    time_t timer;
    time(&timer);
    return ctime(&timer);
}

int
main() {
    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);

    printf("Creating socket...\n");
    SOCKET socket = socket_init(bind_address);
    socket_bind(socket, bind_address);
    freeaddrinfo(bind_address);

    printf("Listening on http://localhost:%d\n", 8080);
    socket_listen(socket);

    SOCKET max_socket = socket;

    printf("Waiting for connections...\n");

    while(1) {
        struct sockaddr* client_sa;
        socklen_t client_sa_len = sizeof(client_sa);
        SOCKET socket_client = socket_accept(socket, client_sa, client_sa_len);

        printf("Client is connected...\n");
        socket_get_info(client_sa, client_sa_len);

        printf("Reading request...\n");
        char request[1024];
        socket_read_client_request(socket_client, request);

        printf("Sending response...\n");
        int bytes_sent = socket_send_response(socket_client);

        char *payload = request;
        bytes_sent = send(socket_client, payload, strlen(payload), 0);

        int payload_len = (int)strlen(payload);

        printf("Sent %d of %d bytes.\n", bytes_sent, payload_len);

        printf("Closing connection...\n");
        CLOSESOCKET(socket_client);
    }

    printf("Closing listening socket...\n");
    CLOSESOCKET(socket);

    printf("Finished.\n");

    return 0;
}
