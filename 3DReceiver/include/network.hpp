#ifndef NETWORK
#define NETWORK

#include "input_data.hpp"

/**
 * @brief connect to ip adress given at port
 * @return fd of socket when connected, or < 0 if error
 */
int connectTo(const char *ipAdress, int port);

/**
 * @brief wait for inputs and put them in the input struct given
 * @return 0 if all clear
 */
int getInputs(int socket_client, inputData *inputs);

#endif