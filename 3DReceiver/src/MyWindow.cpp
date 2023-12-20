#include <iostream>
#include <arpa/inet.h>

#include <QThread>

#include "worker.hpp"
#include "MyWindow.h"

void MyWindow::initThread() {
	this->worker.moveToThread(&this->workerThread);
	this->workerThread.start();
}

MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	this->initThread();

	QObject::connect(this, &MyWindow::sig_connectToIp, &this->worker, &Worker::slot_connectToIp);

	QObject::connect(ui.inputIP, &QLineEdit::textEdited, [=](const QString &ip) {
		char buf[4];
		bool validIpAddress = inet_pton(AF_INET, ip.toStdString().c_str(), buf)>0;

		bool validPort;
		ui.inputPort->text().toInt(&validPort);
		ui.buttonStart->setEnabled(validIpAddress && validPort);
	});

	QObject::connect(ui.buttonStart, &QPushButton::clicked, [=](bool checked) {
		ui.buttonStart->setText(QString("Stop"));
		
		sig_connectToIp(ui.inputIP->text(), ui.inputPort->text().toInt(nullptr));
	});

	QObject::connect(&this->worker, &Worker::sig_receiveData, this, &MyWindow::slot_receiveData);
}

void MyWindow::slot_receiveData(inputData input) {
    std::cout << input.buttons << std::endl;
}
