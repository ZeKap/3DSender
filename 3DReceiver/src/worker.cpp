#include <iostream>

#include "worker.hpp"
#include "network.hpp"

void Worker::slot_connectAndStart(const QString &ip, int port) {
    // connect to client ip
    int sock_client = network::connectTo(ip.toStdString().c_str(), port);
    inputData inputs;

    while (true) {
        // if error while trying to read in the socket, we log and break
        if(network::getInputs(sock_client, &inputs) != 1) {
            std::cerr << "Connection stopped" << std::endl;
            break;
        }
        // we do NOT receive data, we sent it
        sig_receiveData(inputs);
    }
}
