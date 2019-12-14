// File: Client.cpp
// Author: Cody Burrows (dcodyburrows@gmail.com)
// Battleship Plus Plus 0.1
//
// This program starts up a BPP Client, and connects to the server application.
// /////////////////////////////////////////////////////////////////////////////

#include "Client.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main (int argc, char **argv) {
   int sock = 0;
   struct sockaddr_in server_addr;
   const char *hellow = "Hellow from the client!";
   char buffer[1024] = {0};

   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
       perror("FATAL: Socket creation failed.\n");
       return EXIT_FAILURE;
   }

   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(PORT);

   if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
       perror("FATAL: Unsupported address.\n");
       return EXIT_FAILURE;
   }

   if (connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
       perror("FATAL: Socket connection failed!\n");
       return EXIT_FAILURE;
   }

   send(sock, hellow, strlen(hellow), 0);
   printf("Send Hello Message.\n");
   read(sock, buffer, 1024);
   printf("%s\n", buffer);
   return EXIT_SUCCESS;
}
