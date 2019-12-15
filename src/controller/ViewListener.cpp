// File: ViewListener.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This interface specifies the behavior of any ViewListener object. Notable
// subclasses of this include the Model itself, which stores all of the game
// state information, and the ModelProxy, which communicates with the actual
// model over the network.
// /////////////////////////////////////////////////////////////////////////////

#include "Common.h"

class ViewListener {

    public:
    // ADMINISTRATIVE MESSAGES
        /**
          * Tell the ViewListener about the client joining the game.
          * 
          * @param name The name of the player (char *)
          * @param ship_name The Hull designation of the ship the player will be
          *        captaining. (char *)
          * @param ship_type The enum containing the class of ship the player
          *        will be captaining
          * @param fleet Which fleet this player belongs to (0 for team 0, 
          *        anything else for team 1).
          */
        virtual void join(char *name, char *ship_name, ShipType ship_type, 
                          uint8_t fleet) = 0;

        /**
          * Report the client version to determine compatibility.
          * @param ver_string The Version String e.g. 0.1a or 3.14.6
          */
        virtual void version(char *ver_string) = 0;

        /**
          * Report that a client is quitting.
          */
        virtual void quit() = 0;

    // GAMEPLAY MESSAGES
        // TODO DCB fill these in
}
