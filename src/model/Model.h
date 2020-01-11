// File: Model.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This class implements the ViewListener interface, and is responsible for
// storing game state.
// /////////////////////////////////////////////////////////////////////////////

#ifndef MODEL_H
#define MODEL_H
#include "ViewListener.h"
#include "ModelListener.h"
#include <mutex>
#include <vector>

class Model : public ViewListener {

    private:
        // Store all of the clients connected.
        std::vector<ModelListener *> m_ModelListeners;

        // Monitor mutex object to prevent multiple entries into the monitor.
        std::mutex _mutex;

    public:
        Model(){}
        ~Model(){}
        /**
          * Adds a new model listener to the game.
          *
          * @param v The ModelListener object to hold on to
          */
        void register_listener(ModelListener *v);

        /**
          * Report that a client wants to join the game. Note, this is different
          * from register_listener...That is only concerned with keeping all
          * of the clients organized.
          *
          * @param name A NULL-terminated string of the player's name
          * @param chip_name A NULL-terminated string of the ship the player
          *     captains.
          * @param ship_type The class of ship the player is using.
          * @param fleet Which fleet the player is joining: 0 or 1.
          */ 
        void join(char *name, char *ship_name, ShipType ship_type, 
                          uint8_t fleet);

        /**
          * Report the client version to determine compatibility.
          * @param ver_string The Version String e.g. 0.1a or 3.14.6
          */
        void version(char *ver_string);

        /**
          * Report that a client is quitting.
          */
        void quit();
};
#endif
