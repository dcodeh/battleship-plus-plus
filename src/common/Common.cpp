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

void *get_in_addr(struct sockaddr *sa) {
    if (sa -> sa_family == AF_INET) {
        // get ipv4 field
        return &(((struct sockaddr_in *) sa) -> sin_addr);
    } else {
        return &(((struct sockaddr_in6 *) sa) -> sin6_addr);
    }
}

uint8_t send_str_msg_d(int sockfd, const char byte, const char *msg, const char *debug) {
    char buf[128]; // TODO DCB make this a constant somewhere
    strcpy(buf, byte + msg);
    if (send(sockfd, buf, strlen(buf), 0) == -1) {
        if (debug != NULL) {
            perror(debug);
        } else {
            perror("send_str_msg");
        }
        return 1;
    }
    return 0;
}

uint8_t send_str_msg(int sockfd, const char byte, const char *msg) {
    return send_str_msg_d(sockfd, byte, msg, (const char *) NULL);
}

uint8_t send_byte_d(int sockfd, const char byte, const char *debug) {
    const char *b = &byte;
    if (send(sockfd, b, 1, 0) == -1) {
        if (debug != NULL) {
            perror(debug);
        } else {
            perror("send_byte");
        }
        return 1;
    }

    return 0;
}

uint8_t send_byte(int sockfd, const char byte) {
    return send_byte_d(sockfd, byte, (const char *) NULL);
}
