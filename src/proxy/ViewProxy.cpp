// File: ViewProxy.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This class communicates with the remote view over the network. The
// communications are performed through a socket file descriptor, which is
// set up by the server.
// /////////////////////////////////////////////////////////////////////////////

#include "ViewProxy.h"
#include <sys/socket.h>
#include <sys/types.h>

void ViewProxy::version(char *ver_string) {
    printf("send version %s\n", ver_string);
}

void ViewProxy::quit() {
    printf("quit\n");
}

void ViewProxy::info(char *msg) {
    printf("info %s\n", msg);
}

void ViewProxy::err(char *msg) {
    printf("err %s\n", msg);
}

void ViewProxy::set_listener(ViewListener m) {
    m_listener = m;

    if(!fork()) {
        // child process listens
        listen_for_messages();
    }
}

void ViewProxy::listen_for_messages() {
    char buf[BUFSZ];
    int num_bytes;
    while (true) {
        // read a byte
        if ((num_bytes = recv(m_sockfd, buf, 1, 0)) == -1) {
            // TODO DCB when (if ever) will this exit?
            perror("ViewProxy recv");
        }

        // decode it
        switch (buf[0]) {
            case 'V':
                printf("Version Message received\n");
                break;
            default:
                printf("Unsupported message received\n.");
                break;
        }
    }
}
