// File: Common.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This source file defines functions that are used by many things around the
// project...
// /////////////////////////////////////////////////////////////////////////////
#include "Common.h"
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

/// Get the in address from a sockaddr struct.
void *get_in_addr(struct sockaddr *sa) {
    if (sa -> sa_family == AF_INET) {
        // get ipv4 field
        return &(((struct sockaddr_in *) sa) -> sin_addr);
    } else {
        return &(((struct sockaddr_in6 *) sa) -> sin6_addr);
    }
}
