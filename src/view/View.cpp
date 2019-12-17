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
    printf("version %s\n", ver_string);
}

void View::quit() {
    unique_lock<mutex> lock (_mutex);
    print("die\n");
}

void View::info(char *msg) {
    unique_lock<mutex> lock (_mutex);
    printf("info %s\n", msg);
}

void View::err(char *msg) {
    unique_lock<mutex> lock (_mutex);
    printf("err %s\n", msg);
}

void View::set_listener(ViewListener m) {
    m_listener = m;
}
