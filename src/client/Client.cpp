// File: Client.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This program starts up a BPP Client, and connects to the server application.
// /////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "Common.h"
#include "ModelProxy.h"
#include "View.h"

/**
  * This is the entry point for the Client program. It sets up the network 
  * socket, and configures the view, and model proxy for network communication.
  *
  * Usage:
  * $ ./bpp_client ip port
  * For example: ./bpp_client 127.0.0.1 52441 starts a client that will talk 
  * to a server running on the local machine, port 52441.
  *
  * @oaram argc The number of command line arguments (requires 2)
  * @param argv The command line arguments in string form.
  */
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

    // try to connect to the first valid interface
    int sockfd;
    struct addrinfo *p;
    for (p = servinfo; p != NULL; p = p -> ai_next) {
        if ((sockfd = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol)) == -1) {
            perror("socket call failed");
            continue;
        }

        if (connect(sockfd, p -> ai_addr, p -> ai_addrlen) == -1) {
            close(sockfd);
            perror("connect failed");
            continue;
        }

        break;
    }

    // We go in this if block if none of the interfaces are valid.
    if (p == NULL) {
        fprintf(stderr, "Failed to connect to server.\n");
        return EXIT_FAILURE;
    }

    char s[INET6_ADDRSTRLEN];
    inet_ntop(p -> ai_family, get_in_addr((struct sockaddr *) p -> ai_addr), s, sizeof(s));
    printf("Connecting to BPP server %s\n", s);

    // Free up the space used to store the server's address information. Now
    // we'll talk through the socket file descriptor we got.
    freeaddrinfo(servinfo);
    
    View *view = new View();
    ViewListener *proxy = new ModelProxy(sockfd);
    view -> set_listener(proxy);
    ((ModelProxy *) proxy) -> set_listener(view);

    char name[] = "Cody";
    char ship[] = "USS Enterprise";
    ShipType t = ShipType::battleship;
    uint8_t fleet = 4;
    proxy->join(name, ship, t, fleet);

    while (view->alive()) {
        // twiddle your thumbs...
        usleep(15000);  //      ...slowly
        continue;
    }

    // TODO DCB make sure this actually happens once the messages are hooked up
    printf("View exited...closing socket.\n");
    close(sockfd);
    return EXIT_SUCCESS;
}
