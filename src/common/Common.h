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

/**
  * Get the in address from a sockaddr struct.
  * @param sa The sockaddr struct to extract the information from
  * @return The IPv4 or IPv6 address, depending on the type.
  */
void *get_in_addr(struct sockaddr *sa);

enum ShipType {battleship, destroyer, cargo_ship, frigate, submarine,
               aircraft_carrier, cruiser, repair_ship, minesweeper, semi_sub,
               tug, radio_ship};

#endif
