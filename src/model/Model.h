// File: Model.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This class implements the ViewListener interface, and is responsible for
// storing game state.
// /////////////////////////////////////////////////////////////////////////////

#ifndef "MODEL_H"
#define "MODEL_H"
#include "ViewListener.h"
#include "ModelListener.h"
#include <mutex>
#include <vector>

// Monitor mutex object to prevent multiple entries into the monitor.
mutex _mutex;

class Model : public ViewListener {

    private:
        std::vector<ModelListener> m_ModelListeners;

    public:
        /**
          * Default constructor...Do nothing :)
          */
        Model(void) {
        }

        /**
          * Default destructor...Do nothing :)
          * TODO DCB Do I need to destroy the m_ModelListeners object?
          */
        ~Model(void) {
        }

        /**
          * Adds a new model listener to the game.
          *
          * @param v The ModelListener object to hold on to
          */
        void register_listener(ModelListener v);

        // abstract parent functions implemented by this class:
        /// Tell ViewListener about the client joining the game.
        void join(char *name, char *ship_name, ShipType ship_type,
                  uint8_t fleet);

        /// Inform the client of the server version
        void version(char *ver_string);

        /// Rage quit
        void quit();
}
#endif
