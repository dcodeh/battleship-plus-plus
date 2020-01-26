// File: JoinMessage.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This file contains definitions of functions that dress up a StrMessage to
// function as a JoinMessage.
// /////////////////////////////////////////////////////////////////////////////
#include "JoinMessage.h"
#include <stdint.h>
#include <stdlib.h>
#include "Common.h"

JoinMessage::JoinMessage(Message const& m) : StrMessage(m) {}

void JoinMessage::initialize(char *pname, char *sname, ShipType t,
        uint8_t fleet) {

    // TODO DCB make sure everything is null terminated, and doesn't overflow
    char type[2] = {(char) t, '\0'};
    char fleetstr[2] = {(char) fleet, '\0'};
    char *data[4] = {pname, sname, type, fleetstr};
    StrMessage::initialize('J', 4 /* num_strings */, data);
}

uint8_t JoinMessage::get_player_name(char *dst) {
    return StrMessage::get_string(0 /* index */, dst);
}

uint8_t JoinMessage::get_ship_name(char *dst) {
    return StrMessage::get_string(1 /* index */, dst);
}

ShipType JoinMessage::get_ship_class() {
    char type[2];
    StrMessage::get_string(2 /* index */, type);

    return (ShipType) type[0];
}

uint8_t JoinMessage::get_fleet() {
    char fleetstr[2];
    StrMessage::get_string(3 /* index */, fleetstr);

    return (uint8_t) fleetstr[0];
}
