// File: JoinMessage.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This header defines functionality of the Join Message, which is really just
// a particular type of StrMessage
// /////////////////////////////////////////////////////////////////////////////

#ifndef JOINMESSAGE_H
#define JOINMESSAGE_H 

#include "StrMessage.h"
#include "Common.h"
#include <stdint.h>

class JoinMessage : public StrMessage {
    private:
        char *m_player_name;
        char *m_ship_name;
        ShipType m_ship_class;
        uint8_t m_fleet;

    public:
        JoinMessage();

        ~JoinMessage();

        void initialize(char *pname, char *sname, ShipType t, uint8_t fleet);

        char *get_player_name();

        char *get_ship_name();

        ShipType get_ship_class();

        uint8_t get_fleet();
};

#endif
