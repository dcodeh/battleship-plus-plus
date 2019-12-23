// File: Message.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This header defines the Message base class functions.
// Messages have the following format:
// 
//      XXXXXXXX SSSSSSSS SSSSSSSS [ Message Data ]
//      ^ Type ^ ^ Size          ^ ^ Bytes ...... ^
// /////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGE_H
#define MESSAGE_H
#include <stdint.h>
#include <stdbool.h>

class Message {

    protected:
        /**
          * The length of the message data to follow.
          */
        uint16_t m_msg_len;
        char m_type;
        void *m_data;
        bool m_initialized;

    public:
        /**
          * Construct and initialize the protected data members. Do this
          * for sending a message, then call send.
          */
        Message(char type, uint16_t message_length, void *data);

        /**
          * Construct uninitialized data members. Do this for receiving a
          * message, then call decode().
          */
        Message();

        ~Message();

        uint32_t transmit(int sockfd);

        uint32_t decode(char type, uint16_t message_length, void *data);
};

#endif
