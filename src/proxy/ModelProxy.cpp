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
#include "Message.h"
#include "StrMessage.h"
#include "ByteMessage.h"
#include "JoinMessage.h"

/** Send the version across the network to the remote Model */
void ModelProxy::version(char *ver_string) {
    StrMessage *m = new StrMessage();
    m->initialize('V', 1 /* num_strings */, &ver_string);
    m->transmit(m_sockfd);
    delete m;
}

/** Send the game parameters for this palyer to the remote model */
void ModelProxy::join(char *name, char *ship_name, ShipType ship_type,
                      uint8_t fleet) {
    JoinMessage *m = new JoinMessage();
    m->initialize(name, ship_name, ship_type, fleet);
    m->transmit(m_sockfd);
    delete m;
}

/** Inform the remote model that the client is quitting. */
void ModelProxy::quit() {
    ByteMessage *m = new ByteMessage('Q');
    m->transmit(m_sockfd);
    delete m;
}

/** Register a view with this object. */
void ModelProxy::set_listener(ModelListener *v) {
    m_listener = v;
    m_listener_thread = new std::thread(listen_for_messages, m_sockfd);
}

/** Listen for incoming messages from the remote Model. */
void ModelProxy::listen_for_messages(int sockfd) {
    while (true) {
        Message *msg = new Message();
        char type = msg->receive(sockfd);
        switch (type) {
            case 'V':
                printf("Version Message received\n");
                break;

            case 'Q':
                printf("Quit Message received\n");
                break;

            case ':':
                {
                    printf("Info Message Received\n");
                    StrMessage smg(*msg);
                    char buf[128];
                    smg.get_string(0, buf);
                    printf("Data: %s\n", buf);
                    break;
                }

            default:
                printf("Unsupported message received\n");
                break;
        }

        delete msg;
    }
}
