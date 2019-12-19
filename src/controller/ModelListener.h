// File: ModelListener.h
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This interface specifies the behavior of any ModelListener object. Notable
// subclasses of this include the client' View object, and the server's view 
// proxy, which communicates with the client's model proxy over the network.
// /////////////////////////////////////////////////////////////////////////////

#ifndef MODELLISTENER_H
#define MODELLISTENER_H
#include "Common.h"

class ModelListener {

    protected:
        ModelListener() {}
        virtual ~ModelListener() {}
    public:
    // ADMINISTRATIVE MESSAGES
        /**
          * Report the server version to determine compatibility.
          * @param ver_string The Version String e.g. 0.1a or 3.14.6
          */
        virtual void version(char *ver_string) = 0;

        /**
          * Report that a client is quitting.
          */
        virtual void quit() = 0;

        /**
          * A means of passing general text messages to clients.
          *
          * @param msg The message to send.
          */
        virtual void info(char *msg) = 0;

        /**
          * A means of telling the client that the user tried to do something
          * against the rules. This should not be used to tell the client
          * that something went wrong, like a player dropped connection. See
          * info for that.
          *
          * @param msg The reason why what the user did is not allowed.
          */
        virtual void err(char *msg) = 0;

    // GAMEPLAY MESSAGES
        // TODO DCB fill these in
};

#endif 
