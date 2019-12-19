// File: ModelProxy.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This file provides implementations of the various communcation functions
// with the remote model object.
// /////////////////////////////////////////////////////////////////////////////

#include "ModelProxy.h"
#include <sys/socket.h>
#include <sys/types.h>

void ModelProxy::version(char *ver_string) {
    printf("version %s\n", ver_string);
}

void ModelProxy::join(char *name, char *ship_name, ShipType ship_type,
                      uint8_t fleet) {
    printf("Captain %s of the %s (type %d) joined fleet %d\n", name, ship_name,
           ship_type, fleet);
}

void ModelProxy::quit() {
    printf("die\n");
}

void ModelProxy::set_listener(ModelListener *v) {
    m_listener = v;
    m_listener_thread = new std::thread(listen_for_messages, m_sockfd);
}

void ModelProxy::listen_for_messages(int sockfd) {
    char buf[BUFSZ];
    int num_bytes;
    while (true) {
        if((num_bytes = recv(sockfd, buf, 1, 0)) == -1) {
            perror("ModelProxy recv");
        }

        if (num_bytes > 0) {
            switch (buf[0]) {
                case 'V':
                    printf("Version Messages received\n");
                    break;

                default:
                    printf("Unsupported message received\n");
                    break;
            }
        }
    }
}
