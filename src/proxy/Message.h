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
          * The length of the message data to follow. This doesn't include the
          * byte or two used to specify the message type.
          */
        uint16_t m_msg_len;
        char m_type;
        void *m_data; // the meaty good ness that everyone cares about
        bool m_initialized;

    public:
        /**
          * Construct and initialize the protected data members. Do this
          * for sending a message, then call send.
          * TODO DCB Consider moving the initialization out of the constructor
          * because this makes it difficult for child classes to get their
          * data formatted before calling the parent constructor in the
          * initializer list.
          *
          * @param type A byte to mark what type of message follows, and thus 
          *     how it should be decoded.
          * @param message_length The amount of data being sent
          * @param data The actual message--all message_length bytes of it.
          */
        Message(char type, uint16_t message_length, void *data);

        /**
          * Construct uninitialized data members. Do this for receiving a
          * message, then call decode().
          */
        Message();

        /**
          * Don't need to do much to destruct a Message object...TODO DCB or 
          * do you?
          */
        ~Message();

        /**
          * Send the contents of this message over the network using the
          * specified socket file descriptor.
          *
          * @param sockfd The Socket to use to send the data.
          * @return the number of bytes that were read.
          */ 
        uint32_t transmit(int sockfd);

        /**
          * Decode a message sent over the network.
          *
          * @param type The type of message that was received
          * @param message_length The number of bytes in the message
          * @param data What the message says.
          * @return The number of bytes read.
          */
        uint32_t decode(char type, uint16_t message_length, void *data);
};

#endif
