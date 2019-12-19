// File: ViewProxy.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This class communicates with the remote view over the network. The
// communications are performed through a socket file descriptor, which is
// set up by the server.
// /////////////////////////////////////////////////////////////////////////////

#include "ViewProxy.h"
#include <thread>
#include <sys/socket.h>
#include <sys/types.h>

ViewProxy::ViewProxy(int socket_fd) {
    m_sockfd = socket_fd;
    m_listener_thread = NULL;
}

ViewProxy::~ViewProxy() {
    if (m_listener_thread != NULL) {
        delete m_listener_thread;
    }
}

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

void ViewProxy::set_listener(ViewListener *m) {
    m_listener = m;
    m_listener_thread = new std::thread(listen_for_messages, m_sockfd);
}

void ViewProxy::listen_for_messages(int sockfd) {
    char buf[BUFSZ];
    int num_bytes;
    while (true) {
        // read a byte
        if ((num_bytes = recv(sockfd, buf, 1, 0)) == -1) {
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