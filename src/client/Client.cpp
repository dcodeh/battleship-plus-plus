// File: Client.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This program starts up a BPP Client, and connects to the server application.
// /////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main (int argc, char **argv) {
    // check command line arguments
    const char *ip;
    const char *port;
    if (argc == 3) {
        ip = argv[1];
        port = argv[2];
    } else {
        fprintf(stderr, "Usage: $ ./bpp_client server_ip port\n");
        return EXIT_FAILURE;
    }

    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;        // USE IPV 4 or 6 I don't care
    hints.ai_socktype = SOCK_STREAM;    // Use TCP

    status = getaddrinfo(ip, port, &hints, &servinfo);
    if (status != 0) {
        fprintf(stderr, "FATAL: failed to connect to server: %s\n",
                gai_strerror(status));
        return EXIT_FAILURE;
    }

    // TODO DCB do stuff herre

    freeaddrinfo(servinfo);
    return EXIT_SUCCESS;
}
