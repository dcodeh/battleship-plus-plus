// File: View.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This class implements the ModelListener interface, and provides a view to the
// client user.
// /////////////////////////////////////////////////////////////////////////////

#include "View.h"
#include <stdio.h>
#include <mutex>

/** Inform the view of the server's version */
void View::version(char *ver_string) {
    std::unique_lock<std::mutex> lock (_mutex);
    printf("version %s\n", ver_string);
}

/** Inform the view that it should quit. */
void View::quit() {
    std::unique_lock<std::mutex> lock (_mutex);
    printf("die\n");
    m_alive = false;
}

/** Pass a note to the view. */
void View::info(char *msg) {
    std::unique_lock<std::mutex> lock (_mutex);
    printf("info %s\n", msg);
}

/** Give the view a slap on the wrist. */
void View::err(char *msg) {
    std::unique_lock<std::mutex> lock (_mutex);
    printf("err %s\n", msg);
}

/** Hook the view up to a model object */
void View::set_listener(ViewListener *m) {
    m_listener = m;
}

/** Poll whether or not the view is still listening for messages */
bool View::alive() {
    return m_alive;
}
