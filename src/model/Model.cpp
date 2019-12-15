// File: Model.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This class implements the ViewListener interface, and is responsible for
// storing game state.
// /////////////////////////////////////////////////////////////////////////////

#include "Model.h"
#include <mutex>
#include <vector>

/**
  * Adds a new model listener to the game.
  */
void Model::register_listener(ModelListener v) {
    unique_lock<mutex> lock (_mutex);
    m_ModelListeners.push_back(v);
}

void Model::join(char *name, char *ship_name, ShipType ship_type, 
                 uint8_t fleet) {
    // TODO DCB
}

void Model::version(char *ver_string) {
    // TODO DCB
}

void Model::quit() {
    // TODO DCB
}
