// File: Server.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This program starts up a BPP server, and coordinates game play between
// all of the player terminals.
// /////////////////////////////////////////////////////////////////////////////

#include "Server.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>

#include "ViewProxy.h"
#include "Model.h"
#include "ModelListener.h"
#include "ViewListener.h"
#include "Common.h"

void sigchld_handler(int s) {
    printf("sigchld_handler: %d\n", s);
    int saved_errno = errno;
    while(waitpid(-1, NULL, WNOHANG) > 0);
    errno = saved_errno;
}

int main (int argc, char ** argv) {
    const char *port;
    if (argc == 2) {
        port = argv[1];
    } else {
        fprintf(stderr, "Usage: $ ./bpp_server port\n");
        return EXIT_FAILURE;
    }

    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof(hints));   // init to 0
    hints.ai_family = AF_UNSPEC;        // Use whatever ip standard
    hints.ai_socktype = SOCK_STREAM;    // use TCP
    hints.ai_flags = AI_PASSIVE;        // determine IP addr automagically

    status = getaddrinfo(NULL, port, &hints, &servinfo);
    if (status != 0) {
        fprintf(stderr, "FATAL: failed to get host address info: %s\n",
                gai_strerror(status));
        return EXIT_FAILURE;
    }

    // find the first result we can bind to
    int sockfd; // socket file descroptor
    int new_fd; // new connections
    int yes = 1;
    struct addrinfo *p;
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo);

    if (p == NULL) {
        fprintf(stderr, "FATAL: unable to bind server socket.\n");
        return EXIT_FAILURE;
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        return EXIT_FAILURE;
    }

    struct sigaction sa;
    struct sockaddr_storage their_addr;
    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    printf("Waiting for connections\n");

    // accept all new connections
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];
    Model *model = new Model(); // TODO DCB use new?

    // TODO DCB add check for model done listening for new connections
    while (true) {
        sin_size = sizeof(their_addr);
        new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof(s));
        printf("Accepting new connection from %s\n", s);

        // TODO DCB I don't think this is necessary: remove child handling stuff
        // if (!fork()) {
        //     // only run by the child process
        //     close(sockfd);
        //     if(send(new_fd, "HELLOW WORLD!", 13, 0) == -1) {
        //         perror("send");
        //     }
        //     close(new_fd);
        //     // child process exits
        //     return EXIT_SUCCESS;
        // }
        // close(new_fd); // paren't doesn't use this

        printf("Waiting for the magic to happen\n");
        usleep(1500000);
        ModelListener *proxy = new ViewProxy(new_fd);
        model->register_listener(proxy);
        ((ViewProxy *) proxy)->set_listener(model);
    }

    return EXIT_SUCCESS;
}
