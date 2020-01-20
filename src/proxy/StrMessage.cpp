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
#include <stdio.h>

void StrMessage::initialize(char type, uint8_t num_strings, 
        char **str_pointers) {
    // Note: strings are null terminated
    m_num_strings = num_strings;
    m_str_pointers = str_pointers;

    uint16_t total_len = num_strings;
    for (uint8_t i = 0; i < num_strings; ++i) {
        total_len += strlen(str_pointers[i]);
    }

    if (total_len > UINT8_MAX) {
        printf("Warning: Strings are too long!\n");
    }
    char *data = new char[total_len];

    char *tmp = data;
    for (uint8_t i = 0; i < num_strings; ++i) {
        uint8_t len = strlen(str_pointers[i]);
        *tmp = (char) len; // TODO DCB overflowing?
        tmp += 1;
        strncpy(tmp, str_pointers[i], len);
        tmp += len;
    }

    Message::initialize(type, total_len, data);
}

/** Create an empty String Message object */
StrMessage::StrMessage() : Message() {
    m_initialized = false;
}

/** Drop a nuke on your string message */
StrMessage::~StrMessage() {
    // TODO DCB Memory Leaks :)
}

/** Break a blob of data into the number of strings that it represents. */
uint32_t StrMessage::decode(uint16_t message_length, char *data) {
    uint8_t total_msg_len = Message::get_msg_size();
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

/** Provide a way to access strings once they're parsed from a received msg. */
uint8_t StrMessage::get_string(uint8_t index, char *dest) {
    if (index < m_num_strings) {
        uint8_t len = m_str_lengths[index];
        strncpy(dest, m_str_pointers[index], len);
        return len;
    } else {
        return 0;
    }
}
