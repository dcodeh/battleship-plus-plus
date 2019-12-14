// File: Client.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This program starts up a BPP Client, and connects to the server application.
// /////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static const char *usage = "Usage: $ bpp_client server_ip port";

/**
  * Usage: ./bpp_client server_ip port
  */
int main (int argc, char **argv) {
    // check usage:
    char *ip_addr_str = NULL;
    char *port_str = NULL;
    if (argc == 3) {
        ip_addr_str = argv[1];
        port_str = argv[2];
    } else {
        perror(usage);
        return EXIT_FAILURE;
    }

    uint16_t port_num = (uint16_t) strtoul(port_str, NULL /* endptr*/, 
                                           10 /* base */);
    int sock = 0;
    struct sockaddr_in server_addr;
    const char *hellow = "Hellow from the client!";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("FATAL: Socket creation failed.\n");
        return EXIT_FAILURE;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_num);

    if (inet_pton(AF_INET, ip_addr_str, &server_addr.sin_addr) <= 0) {
        perror("FATAL: Unsupported address.\n");
        close(sock);
        return EXIT_FAILURE;
    }

    if (connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("FATAL: Socket connection failed!\n");
        close(sock);
        return EXIT_FAILURE;
    }

    send(sock, hellow, strlen(hellow), 0);
    printf("Send Hello Message.\n");
    read(sock, buffer, 1024);
    printf("%s\n", buffer);
    close(sock);
    return EXIT_SUCCESS;
}
