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

        void join(char *name, char *ship_name, ShipType ship_type,
                  uint8_t fleet);

        void version(char *ver_string);

        void quit();

        void set_listener(ModelListener *v);
};

#endif
