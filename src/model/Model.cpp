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
void Model::register_listener(ModelListener *v) {
    std::unique_lock<std::mutex> lock (_mutex);
    m_ModelListeners.push_back(v);
    printf("ModelListener registered\n");
    char infomsg[] = "You've been successfully connected";
    v->info(infomsg);
    v->quit();
}

/** Report information required to join a game */
void Model::join(char *name, char *ship_name, ShipType ship_type, 
                 uint8_t fleet) {
    std::unique_lock<std::mutex> lock (_mutex);
    printf("Captain %s of %s (type %d) joined fleet %d\n", name, ship_name,
           ship_type, fleet);
}

/** Report the client version to the server */
void Model::version(char *ver_string) {
    std::unique_lock<std::mutex> lock (_mutex);
    printf("version %s\n", ver_string);
}

/** Report that the client is quitting (maybe due to rage). */
void Model::quit() {
    std::unique_lock<std::mutex> lock (_mutex);
    printf("goodbye cruel world\n");
}
