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
#include "Common.h"

/** Send the version across the network to the remote Model */
void ModelProxy::version(char *ver_string) {
    printf("version %s\n", ver_string);
}

/** Send the game parameters for this palyer to the remote model */
void ModelProxy::join(char *name, char *ship_name, ShipType ship_type,
                      uint8_t fleet) {
    printf("Captain %s of the %s (type %d) joined fleet %d\n", name, ship_name,
           ship_type, fleet);
}

/** Inform the remote model that the client is quitting. */
void ModelProxy::quit() {
    printf("die\n");
}

/** Register a view with this object. */
void ModelProxy::set_listener(ModelListener *v) {
    m_listener = v;
    m_listener_thread = new std::thread(listen_for_messages, m_sockfd);
}

/** Listen for incoming messages from the remote Model. */
void ModelProxy::listen_for_messages(int sockfd) {
    char buf[BUFSZ];
    int num_bytes;
    while (true) {
        printf("Hellow from modelproxy.\n");
        if((num_bytes = recv(sockfd, buf, 1, 0)) == -1) {
            perror("ModelProxy recv");
        }

        if (num_bytes > 0) {
            switch (buf[0]) {
                case 'V':
                    printf("Version Message received\n");
                    break;

                case 'Q':
                    printf("Quit Message received\n");
                    break;

                default:
                    printf("Unsupported message received\n");
                    break;
            }
        }
    }
}
