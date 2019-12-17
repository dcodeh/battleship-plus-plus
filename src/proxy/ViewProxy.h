// File: ViewProxy.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This file exports all of the functions that the ViewProxy class implements.
// /////////////////////////////////////////////////////////////////////////////

#ifndef "VIEWPROXY_H"
#define "VIEWPROXY_H"

#include "ModelListener.h"
#include "ViewListener.h"
#include <thread>
#define BUFSZ 1024

class ViewProxy : public ModelListener {

    private:
        int m_sockfd;
        ViewListener m_listener;
        std::thread *m_listener_thread;

        void listen_for_messages();

    public:
        ViewProxy(int socket_fd) {
            m_sockfd = socket_fd;
            m_listener_thread = NULL;
        }

        ~ViewProxy() {
            if (m_listener_thread != NULL) {
                delete m_listener_thread;
            }
        }

        void version (char *ver_string);

        void quit();

        void info(char *msg);

        void err(char *msg);

        void set_listener(ViewListener m);
}

#endif
