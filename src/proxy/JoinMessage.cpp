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

JoinMessage::JoinMessage() : StrMessage() {
    m_player_name = NULL;
    m_ship_name = NULL;
    m_ship_class = ShipType::battleship;
    m_fleet = 0;
}

JoinMessage::~JoinMessage() {
    // TODO DCB memory leak :)
}
// 
// void JoinMessage::initialize(char *pname, char *sname, ShipType t,
//         uint8_t fleet) {
//     
// }
