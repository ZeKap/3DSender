#include <iostream>

#include "worker.hpp"

void Worker::slot_connectToIp(const QString &ip, int port) {
    std::cout << "uwu i'm supposed to connect now" << std::endl;
    while (true) {
        auto input = inputData {
            .buttons = 1,
        };
        // we do NOT receive data, we sent it
        sig_receiveData(input);
    }
}
