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

        void version(char *ver_string);

        void quit();

        void info(char *msg);

        void err(char *msg);

        void set_listener(ViewListener *m);

        bool alive();
};

#endif
