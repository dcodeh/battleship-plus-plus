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

    // TODO DCB remove this
    printf("Connecting to %s port %s\n", ip, port);
    View v();
    ModelProxy mp();

//    int status;
//    struct addrinfo hints;
//    struct addrinfo *servinfo;
//
//    memset(&hints, 0, sizeof(hints));
//    hints.ai_family = AF_UNSPEC;        // USE IPV 4 or 6 I don't care
//    hints.ai_socktype = SOCK_STREAM;    // Use TCP
//
//    status = getaddrinfo(ip, port, &hints, &servinfo);
//    if (status != 0) {
//        fprintf(stderr, "FATAL: failed to connect to server: %s\n",
//                gai_strerror(status));
//        return EXIT_FAILURE;
//    }
//
//    // try to connect to the first valid interface
//    int sockfd;
//    struct addrinfo *p;
//    for (p = servinfo; p != NULL; p = p -> ai_next) {
//        if ((sockfd = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol)) == -1) {
//            perror("socket call failed");
//            continue;
//        }
//
//        if (connect(sockfd, p -> ai_addr, p -> ai_addrlen) == -1) {
//            close(sockfd);
//            perror("connect failed");
//            continue;
//        }
//
//        break;
//    }
//
//    if (p == NULL) {
//        fprintf(stderr, "Failed to connect to server.\n");
//        return EXIT_FAILURE;
//    }
//
//    char s[INET6_ADDRSTRLEN];
//    inet_ntop(p -> ai_family, get_in_addr((struct sockaddr *) p -> ai_addr), s, sizeof(s));
//    printf("Connecting to BPP server %s\n", s);
//
//    freeaddrinfo(servinfo);
//
//    char buf[100];
//    int numbytes;
//    if ((numbytes = recv(sockfd, buf, 99, 0)) == -1) {
//        perror("recv");
//        return EXIT_FAILURE;
//    }
//
//    buf[numbytes] = '\0';
//    printf("received %s\n", buf);
//
//    close(sockfd);
    return EXIT_SUCCESS;
}
