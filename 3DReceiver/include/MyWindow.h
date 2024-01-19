#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QThread>
#include <QString>
#include <arpa/inet.h>

#include "ui_template.h"
#include "worker.hpp"

class MyWindow : public QWidget
{
	Q_OBJECT
public:
	// Initialize the thread (worker)
	void initThread();
	// Constructor, default parent is 0
	explicit MyWindow(QWidget *parent = 0);
private:
	// Ui shown to user
	Ui::root ui;
	// Class running "inside" workerThread, responsible for sending and receiving socket data
	Worker worker;
	// Thread used by worker
	QThread workerThread;
signals:
	// Tell the thread to connect and start giving inputs
	void sig_connectAndStart(const QString &ip, int port);
public slots:
	// When getting inputs, manage what to do of them
	void slot_receiveData(inputData input);
};

#endif // MYWINDOW_H
