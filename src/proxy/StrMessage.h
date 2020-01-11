// File: StrMessage.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This header defines the functionality of a String Message. The blob of data
// from the parent Message class is parsed, and string parts are extracted
// based on their lengths.
// /////////////////////////////////////////////////////////////////////////////

#ifndef STRMESSAGE_H
#define STRMESSAGE_H

#include "Message.h"
#include <stdint.h>

class StrMessage : public Message {

    private:
        // The number of strings in the message
        uint8_t m_num_strings;
        // An array of pointers to the first char of each string in the message.
        char ** m_str_pointers;
        // A pointer to an array storing how long each string is.
        uint8_t *m_str_lengths;

    public:
        /**
          * Construct a new String message to be sent over the network.
          *
          * @param type The identifying message byte
          * @param num_strings The number of strings to send in the body of the
          *     message.
          * @param str_pointers A pointer to all of the strings to be sent, one
          *     right after the other.
          */
        StrMessage(char type, uint8_t num_strings, char **str_pointers);

        /**
          * Make an empty String Message. This can't be sent over the network
          * until the data fields are populated.
          */ 
        StrMessage();

        /**
          * Murder a String Message in cold blood.
          */
        ~StrMessage();

        /**
          * Send the string(s) over the network.
          *
          * @param sockfd The socket file descriptor to use
          * @return the number of bytes sent
          */
        uint32_t transmit(int sockfd);

        /**
          * Make sense of a string message that came in over the network.
          *
          * @param type the type of message that was sent
          * @param message_length The total length of the blob that was received
          * @param data The nugget of goodness we want to break open.
          */
        uint32_t decode(char type, uint16_t message_length, void *data);

        /**
          * Once a message has been received, get a pointer to the nth string
          * in the data structure. If an invalid index is passed, dest will be 
          * unchanged, and the method will return 0.
          *
          * @param index The index of the string received...e.g. 0 for the first
          *     one, 1 for the second, and so on.
          * @param dest A pointer to a string that can be overwritten with the
          *     location of the requested string.
          * @return The length of the string that dest points to.
          */
        uint8_t get_string(uint8_t index, char *dest);
};

#endif
