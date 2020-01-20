// File: ByteMessage.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This header defines things for sending a single byte over the network.
// /////////////////////////////////////////////////////////////////////////////

#ifndef BYTEMESSAGE_H
#define BYTEMESSAGE_H
#include "Message.h"
#include <stdint.h>
#include <stdbool.h>

class ByteMessage : public Message {

    public:
        /**
          * Construct and initialize the protected data members. Do this
          * for sending a message, then call send.
          */
        ByteMessage(char type);
};

#endif
