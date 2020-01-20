// File: Message.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This header defines the Message base class functions.
// Messages have the following format:
// 
//      XXXXXXXX SSSSSSSS [ Message Data ]
//      ^ Type ^ ^ Size ^ ^ Size Bytes.. ^
// /////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGE_H
#define MESSAGE_H
#include <stdint.h>
#include <stdbool.h>

#define MAX_MSG_LEN 255

class Message {

    protected:
        /**
          * The length of the message data to follow. This doesn't include the
          * byte or two used to specify the message type.
          */
        uint8_t m_msg_len;
        char m_type;
        char *m_data; // the meaty goodness that everyone cares about
        bool m_initialized;

    public:
        /**
          * Construct a message with blank contents.
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
          * Use this function to receive a message and store the data inside 
          * this object. This will block until a whole message is received.
          * The internal state of this object will be overwritten.
          * 
          * @param sockfd The Socket to listen for a message on
          * @return the type of the message received
          */
        char receive(int sockfd);

        /**
          * @return the type byte of this message.
          */
        char get_msg_type();


        /**
          * @return the length of the data buffer
          */
        uint8_t get_msg_size();
         
        /**
          * Change the internal state of this message.
          *
          * @param type The type character of this message
          * @param msg_len The length of the message
          * @param data A pointer to the data buffer for this message.
          */
        void initialize(char type, uint8_t msg_len, char *data);

    private:
        /**
          * Copy the data buffer somewhere else.
          *
          * @param dest A destination buffer to copy the data buffer to
          * @return the number of bytes copied
          */
        uint8_t get_data_buffer(char *dest);
};

#endif
