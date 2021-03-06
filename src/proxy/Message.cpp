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
#include <string.h>
#include "ByteMessage.h"

/// Construct a new message without knowing what should go in it yet...
Message::Message() {
    m_msg_len = 0;
    m_type = '\0';
    m_data = NULL;
    m_initialized = false;
}

Message::Message(Message const& m) {
    m_msg_len = m.get_msg_size();
    m_type = m.get_msg_type();
    m_data = new char[m_msg_len];
    m.get_data_buffer(m_data);
    m_initialized = m.get_initialized();
}

/// Kill a message.
Message::~Message() {
    if (m_initialized) {
        delete m_data;
    }
}

/// Send the data stored in the message over a socket.
uint32_t Message::transmit(int sockfd) {
    if (m_initialized) {
        int sent = 0;
        // send the type of the message
        sent += send(sockfd, &m_type, 1, 0);
        char len_char = (char) m_msg_len;
        sent += send(sockfd, &len_char, 1, 0);
        sent += send(sockfd, m_data, m_msg_len, 0);
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

char Message::receive(int sockfd) {
    uint8_t len;
    uint8_t total_received = 0;
    int num_bytes;
    char type;
    const uint16_t buflen = MAX_MSG_LEN + 2;
    char buf[buflen];
    char *bufstart = buf;
    bool recvdone = false;

    while (!recvdone) {
        num_bytes = recv(sockfd, bufstart, 1, 0);
        if (num_bytes < 0) {
            perror("Message recv type");
        } else if(num_bytes == 1) {
            recvdone = true;
            type = bufstart[0];
            bufstart = buf + 1;
        }
    }
    printf("Received type %c\n", type);

    recvdone = false;
    while (!recvdone) {
        num_bytes = recv(sockfd, bufstart, 1, 0);
        if (num_bytes < 0) {
            perror("Message recv len");
        } else if(num_bytes == 1) {
            recvdone = true;
            len = (uint8_t) bufstart[0];
            bufstart = buf + 2;
        }
    }
    printf("Received size %d\n", len);

    recvdone = false;
    while (!recvdone && len > 0) {
        num_bytes = recv(sockfd, bufstart, 1, 0);
        if (num_bytes < 0) {
            perror("Message recv data");
        } else if(num_bytes == 1) {
            total_received++;
            bufstart++; // increment the pointer
            if (total_received == len) {
                recvdone = true;
            }
        }
    }

    m_type = type;
    m_msg_len = len;
    if (m_initialized) {
        delete m_data;
    }
    m_data = new char[m_msg_len];
    memcpy(m_data, buf + 2, m_msg_len); // skip type and size
    printf("Received data %s\n", m_data);

    m_initialized = true;
    return type;
}

char Message::get_msg_type() const {
    return m_type;
}

uint8_t Message::get_msg_size() const {
    return m_msg_len;
}

void Message::initialize(char type, uint8_t msg_len, char *data) {
    if (m_initialized) {
        delete m_data;
    }
    m_type = type;
    m_data = new char[msg_len];
    memcpy(m_data, data, msg_len);
    m_msg_len = msg_len;
    m_initialized = true;
}

bool Message::get_initialized() const {
    return m_initialized;
}

uint8_t Message::get_data_buffer(char *dest) const {
    if (m_initialized) {
        memcpy(dest, m_data, m_msg_len);
        return m_msg_len;
    } else {
        return 0;
    }
}
