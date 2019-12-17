// File: Model.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This class implements the ViewListener interface, and is responsible for
// storing game state.
// /////////////////////////////////////////////////////////////////////////////

#include "Model.h"
#include <stdio.h>
#include <mutex>
#include <vector>

/**
  * Adds a new model listener to the game.
  */
void Model::register_listener(ModelListener v) {
    unique_lock<mutex> lock (_mutex);
    m_ModelListeners.push_back(v);
    v.info("You've been successfully connected.");
    v.info("Goodbye");
    v.quit();
}

void Model::join(char *name, char *ship_name, ShipType ship_type, 
                 uint8_t fleet) {
    unique_lock<mutex> lock (_mutex);
    printf("Captain %s of %s (type %d) joined fleet %d\n", name, ship_name,
           ship_type, fleet);
}

void Model::version(char *ver_string) {
    unique_lock<mutex> lock (_mutex);
    printf("version %s\n", ver_string);
}

void Model::quit() {
    unique_lock<mutex> lock (_mutex);
    printf("goodbye cruel world\n");
}
