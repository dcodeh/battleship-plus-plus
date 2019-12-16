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

void View::version(char *ver_string) {
    unique_lock<mutex> lock (_mutex);
    // TODO DCB
}

void View::quit() {
    unique_lock<mutex> lock (_mutex);
    // TODO DCB
    exit(0);
}

void View::info(char *msg) {
    unique_lock<mutex> lock (_mutex);
    printf("%s\n", msg);
}

void View::err(char *msg) {
    unique_lock<mutex> lock (_mutex);
    // TODO DCB
}

void View::set_listener(ViewListener m) {
    m_listener = m;
}
