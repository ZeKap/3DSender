#pragma once
#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <3ds.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include "printer.hpp"

void launch_test_server();

char * test_get_IP();

// returns true if everything went ok
Result init_network();

#endif