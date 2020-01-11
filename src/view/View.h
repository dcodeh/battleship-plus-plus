// File: View.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This header exports the functions that the view implements in the
// ViewListener interface.
// /////////////////////////////////////////////////////////////////////////////

#ifndef VIEW_H
#define VIEW_H

#include "ModelListener.h"
#include "ViewListener.h"
#include <mutex>
#include <stdbool.h>

class View : public ModelListener {


    private:
        ViewListener *m_listener;
        std::mutex _mutex;
        bool m_alive;
    public:
        /** 
          * Default Constructor...
          */
        View() {
            m_alive = true;
        }

        /**
          * Default Destructor...
          */

        ~View() {
        }

        /**
          * Tell the view the server's version.
          *
          * @param ver_string The version string, such as 10.15.3
          */
        void version(char *ver_string);

        /**
          * Tell the view the server wants it to quit.
          */
        void quit();

        /**
          * Deliver an information message from the server
          *
          * @param msg The message
          */
        void info(char *msg);

        /**
          * Deliver an error message from the server, likely indicating that the
          * view did something wrong. Punishment not yet implemented.
          *
          * @param msg What went wrong
          */
        void err(char *msg);

        /**
          * Hook up the model (or listener) that listens to this object.
          *
          * @param m The Model.
          */
        void set_listener(ViewListener *m);

        /**
          * Poll whether or not the view is still listening for messages.
          *
          * @return true if the view is still listening. False otherwise.
          */
        bool alive();
};

#endif
