// File: ViewProxy.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This class communicates with the remote view over the network. The
// communications are performed through a socket file descriptor, which is
// set up by the server.
// /////////////////////////////////////////////////////////////////////////////

#include "ViewProxy.h"
#include "Common.h"
#include <thread>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "Message.h"
#include "StrMessage.h"
#include "ByteMessage.h"

/** Create a new ViewProxy */
ViewProxy::ViewProxy(int socket_fd) {
    m_sockfd = socket_fd;
    m_listener_thread = NULL;
}

/** Kick a ViewProxy out of memory */
ViewProxy::~ViewProxy() {
    if (m_listener_thread != NULL) {
        delete m_listener_thread;
    }
}

/** Send the version of the server to the client. */
void ViewProxy::version(char *ver_string) {
    StrMessage *m = new StrMessage();
    m->initialize('V', 1 /* num_strings */, &ver_string);
    m->transmit(m_sockfd);
    delete m;
}

/** Tell the client they should quit. */
void ViewProxy::quit() {
    Message *m = new ByteMessage('Q');
    m->transmit(m_sockfd);
    delete m;
}

/** Tell the client some information */
void ViewProxy::info(char *msg) {
    StrMessage *m = new StrMessage();
    m->initialize(':', 1 /* num_strings*/, &msg);
    m->transmit(m_sockfd);
    delete m;
}

/** Tell the client they did something wrong. */
void ViewProxy::err(char *msg) {
    StrMessage *m = new StrMessage();
    m->initialize('~', 1 /* num_strings */, &msg);
    m->transmit(m_sockfd);
    delete m;
}

/** Connect this proxy to the real server model. */
void ViewProxy::set_listener(ViewListener *m) {
    m_listener = m;
    m_listener_thread = new std::thread(listen_for_messages, m_sockfd);
}

/**
  * Listen for incoming messages from the remote clienti, and decide what to
  * do about them...
  */
void ViewProxy::listen_for_messages(int sockfd) {
    while (true) {
        // read a byte
        Message *msg = new Message();
        char type = msg->receive(sockfd);
        switch (type) {
            case 'V':
                printf("Version Message received\n");
                break;
            default:
                printf("Unsupported message received\n");
                break;
        }
    }
}
