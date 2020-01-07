// File: Message.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// Message base class implementation.
// /////////////////////////////////////////////////////////////////////////////

#include "Message.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

Message::Message(char type, uint16_t message_length, void *data) {
    m_type = type;
    m_msg_len = message_length;
    m_data = data;
    m_initialized = true;
}

Message::Message() {
    m_initialized = false;
}

Message::~Message() {
}

uint32_t Message::transmit(int sockfd) {
    if (m_initialized) {
        int sent = 0;
        // send the type of the message
        sent += send(sockfd, &m_type, 1, 0);
        sent += send(sockfd, (char *) m_data, m_msg_len, 0);
        printf("Message send %d bytes\n", sent);
        if (sent == -1) {
            perror(m_type + " failed to send");
            return 0;
        } else {
            return (uint32_t) sent;
        }
    } else {
        return 0;
    }
}

uint32_t Message::decode(char type, uint16_t message_length, void *data) {
    // There's nothing to really decode....
    m_type = type;
    m_msg_len = message_length;
    m_data = data;

    return m_msg_len;
}
