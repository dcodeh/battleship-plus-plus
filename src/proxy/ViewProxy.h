// File: ViewProxy.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This file exports all of the functions that the ViewProxy class implements.
// /////////////////////////////////////////////////////////////////////////////

#ifndef VIEWPROXY_H
#define VIEWPROXY_H

#include "ModelListener.h"
#include "ViewListener.h"
#include <thread>
#define BUFSZ 1024 // TODO DCB move this to a constant somehweres

class ViewProxy : public ModelListener {

    private:
        int m_sockfd;
        ViewListener *m_listener;
        std::thread *m_listener_thread;

        /** A thread that listens for messages from the remote view. */
        static void listen_for_messages(int sockfd);

    public:
        /**
          * Create a new ViewProxy using a particular socket file descriptor.
          *
          * @param socket_fd The socket file descriptor to use to communicate
          *     with the remove view.
          */
        ViewProxy(int socket_fd);

        /** Dash the hopes and dreams of a ViewProxy Object. */
        ~ViewProxy();

        /**
          * Send the remote view the version of the server.
          *
          * @param ver_string The version string, such as 0.1.6a
          */
        void version (char *ver_string);

        /**
          * Tell the remote client that it should quit the game. 
          */
        void quit();

        /**
          * Send a general information message to the client.
          *
          * @param msg The message to send, null terminated.
          */
        void info(char *msg);

        /**
          * Send an error message to the client.
          *
          * @param msg The message to send, null terminated.
          */
        void err(char *msg);

        /**
          * Register the model with this proxy object.
          */
        void set_listener(ViewListener *m);
};

#endif
