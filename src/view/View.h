// File: View.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This header exports the functions that the view implements in the
// ViewListener interface.
// /////////////////////////////////////////////////////////////////////////////

#ifndef "VIEW_H"
#define "VIEW_H"

#include "ModelListener.h"
#include <mutex>

mutex _mutex;

class View : public ModelListener {

    public:
        /** 
          * Default Constructor...
          */
        View() {
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
}

#endif
