// File: Server.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This program starts up a BPP server, and coordinates game play between
// all of the player terminals.
// /////////////////////////////////////////////////////////////////////////////

#include "Server.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static const char *USAGE = "Usage: $ ./bpp_server ip_addr port";

int main (int argc, char ** argv) {

    const char *ip_str;
    const char *port_str;
    if (argc == 3) {
        ip_str = argv[1];
        port_str = argv[2];
    } else {
        perror(USAGE);
        return EXIT_FAILURE;
    }

    int32_t server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *hellow = "Hellow World!";

    // Create the file descriptor for the socket
    if (!(server_fd = socket(AF_INET, SOCK_STREAM, 0))) {
        perror("FATAL: Socket creation failed.\n");
        return EXIT_FAILURE;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                sizeof(opt))) {
        perror("FATAL: Could not configure socket options.\n");
        close(server_fd);
        return EXIT_FAILURE;
    }

    address.sin_family = AF_INET;
    // address.sin_addr.s_addr = INADDR_ANY; // binds to all interfaces
    inet_pton(AF_INET, ip_str, &(address.sin_addr));
    uint16_t portnum = (uint16_t) strtoul(port_str, NULL /* endptr */, 10 /* base */);
    address.sin_port = htons(portnum);

    // binding time!
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("FATAL: Failed to bind socket.\n");
        close(server_fd);
        return EXIT_FAILURE;
    }

    if (listen(server_fd, 3) < 0) {
        perror("FATAL: Listening Failed.\n");
        close(server_fd);
        return EXIT_FAILURE;
    }

    if ((new_socket = accept(server_fd,(struct sockaddr *) &address, 
                (socklen_t *) &addrlen)) < 0) {
        perror("FATAL: Failed to accept socket connection!.\n");
        close(server_fd);
        return EXIT_FAILURE;
    }

    read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, hellow, strlen(hellow), 0);
    printf("Sent Message.\n");
    close(server_fd);
    return EXIT_SUCCESS;
}
