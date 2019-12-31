// File: StrMessage.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This class breaks the message data up into strings that can be accessed by 
// index when received.
// /////////////////////////////////////////////////////////////////////////////
#include "StrMessage.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// Note: strings are null terminated
StrMessage::StrMessage(char type, uint8_t num_strings, char **str_pointers) {
    // TODO DCB this is bad inheritance
    m_num_strings = num_strings;
    m_str_pointers = str_pointers;

    uint16_t total_len = num_strings;
    for (uint8_t i = 0; i < num_strings; ++i) {
        total_len += strlen(str_pointers[i]);
    }

    char *data = new char[total_len];
    m_msg_len = total_len;

    char *tmp = data;
    for (uint8_t i = 0; i < num_strings; ++i) {
        uint8_t len = strlen(str_pointers[i]);
        *tmp = (char) len; // TODO DCB overflowing?
        tmp += 1;
        strncpy(tmp, str_pointers[i], len);
        tmp += len;
    }

    m_type = type;
    m_msg_len = total_len;
    m_data = (void *) data;
}

StrMessage::StrMessage() {
    m_initialized = false;
}

StrMessage::~StrMessage() {
    delete (char *)m_data;
    delete m_str_pointers;
}

uint32_t StrMessage::decode(char type, uint16_t message_length, void *data) {
    uint32_t total_msg_len = Message::decode(type, message_length, data);
    char *ptr = (char *) &data;
    uint8_t num_strings = 0;

    while (ptr < (char *)data + message_length) {
        uint8_t len = (uint8_t) *ptr;
        ++num_strings;
        ptr = ptr + len + 1;
    }

    m_num_strings = num_strings;
    m_str_pointers = new char *[m_num_strings];
    m_str_lengths = new uint8_t[m_num_strings];

    ptr = (char *) &data;
    for (uint8_t i = 0; i < m_num_strings; ++i) {
        uint8_t len = (uint8_t) *ptr;
        ++ptr;
        m_str_pointers[i] = ptr;
        m_str_lengths[i] = len;
        ptr += len;
    }

    m_initialized = true;
    return total_msg_len;
}

uint8_t StrMessage::get_string(uint8_t index, char *dest) {
    if (index < m_num_strings) {
        uint8_t len = m_str_lengths[index];
        strncpy(dest, m_str_pointers[index], len);
        return len;
    } else {
        return 0;
    }
}
