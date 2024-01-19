#ifndef DS_WORKER
#define DS_WORKER

#include<QObject>
#include<QString>
#include "input_data.hpp"

// Class responsible for sending and receiving socket data
class Worker : public QObject {
    Q_OBJECT

public slots:
    // called by main thread to tell the worker where to connect
    void slot_connectAndStart(const QString &ip, int port);

signals:
    // called by worker when it has data to transmit
    void sig_receiveData(inputData);
};

#endif
