// File: ByteMessage.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// Implements a single byte message.
// /////////////////////////////////////////////////////////////////////////////

#include "ByteMessage.h"
#include <stdlib.h>

ByteMessage::ByteMessage(char type)  : Message(type, 0, NULL) {
}

ByteMessage::ByteMessage() : Message() {
    m_initialized = false;
}
