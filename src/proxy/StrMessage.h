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
        uint8_t m_num_strings;
        char ** m_str_pointers;
        uint8_t *m_str_lengths;

    public:
        StrMessage(char type, uint8_t num_strings, char **str_pointers);

        StrMessage();

        ~StrMessage();

        uint32_t transmit(int sockfd);

        uint32_t decode(char type, uint16_t message_length, void *data);

        uint8_t get_string(uint8_t index, char *dest);
};

#endif
