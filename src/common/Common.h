// File: Common.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This header file contains declarations and globals that are used by all of 
// the modules in the project.
// /////////////////////////////////////////////////////////////////////////////

#ifndef COMMON_H
#define COMMON_H

#include <sys/socket.h>
#include <stdint.h>

/**
  * Get the in address from a sockaddr struct.
  * @param sa The sockaddr struct to extract the information from
  * @return The IPv4 or IPv6 address, depending on the type.
  */
void *get_in_addr(struct sockaddr *sa);

enum ShipType {battleship, destroyer, cargo_ship, frigate, submarine,
               aircraft_carrier, cruiser, repair_ship, minesweeper, semi_sub,
               tug, radio_ship};

uint8_t send_str_msg_d(int sockfd, const char byte, const char *msg, const char *debug);

uint8_t send_str_msg(int sockfd, const char byte, const char *msg);

uint8_t send_byte_d(int sockfd, const char byte, const char *debug);

uint8_t send_byte(int sockfd, const char byte);

#endif
