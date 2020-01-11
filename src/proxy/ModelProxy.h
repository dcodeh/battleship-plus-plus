// File: ModelProxy.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This file exports all of the functions implemented by the ModelProxy class.
// /////////////////////////////////////////////////////////////////////////////

#ifndef MODEL_PROXY_H
#define MODEL_PROXY_H

#include <thread>
#include "ModelProxy.h"
#include "ViewProxy.h"
#define BUFSZ 1024 // TODO DCB make this a global constant or something

class ModelProxy : public ViewListener {

    private: 
        // the socket we're talking to the real model with
        int m_sockfd;
        ModelListener *m_listener;
        std::thread *m_listener_thread;

        static void listen_for_messages(int sockfd);

    public:
        ModelProxy(int sockfd) {
            m_sockfd = sockfd;
            m_listener_thread = NULL;
        }

        ~ModelProxy() {
            if (m_listener_thread != NULL) {
                delete m_listener_thread;
            }
        }

        /**
          * Inform the model that the player wants to join the game with
          * the specified parameters.
          *
          * @param name The player's reported name (e.g. Geoff)
          * @param ship_name The name of the ship the player is commanding
          * @param ship_type The class of ship that the player is captaining.
          * @param fleet The fleet the player wants to join -- either 0 or 1
          */
        void join(char *name, char *ship_name, ShipType ship_type,
                  uint8_t fleet);

        /**
          * Report the client's version to the server.
          */
        void version(char *ver_string);

        /**
          * Report that the client is leaving the game.
          */
        void quit();

        /**
          * Configure the listener (the view) of this object 
          */
        void set_listener(ModelListener *v);
};

#endif
