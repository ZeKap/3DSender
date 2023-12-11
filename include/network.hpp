#pragma once
#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <3ds.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include "printer.hpp"

int launch_server();
int accept_client(int sock_server);
bool read_client_msg(int sock_client);
bool write_client_msg(int sock_client, const void *data, size_t size);

char *get_IP();

void send_new_inputs_to_client(int sock_client_fd, u32 kheld);

// returns true if everything went ok
Result init_network();

#endif