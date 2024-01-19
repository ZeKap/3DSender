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
	// Add components created in .ui file to this window
	ui.setupUi(this);
	this->initThread();

	// When we call "sig_connectAndStart" in this instance, call "slot_connectAndStart" in the instance of the Worker of this instance
	QObject::connect(this, &MyWindow::sig_connectAndStart, &this->worker, &Worker::slot_connectAndStart);

	// Called when inputIP in ui is edited
	QObject::connect(ui.inputIP, &QLineEdit::textEdited, [=](const QString &ip) {
		char buf[4];
		bool validIpAddress = inet_pton(AF_INET, ip.toStdString().c_str(), buf)>0;

		bool validPort;
		ui.inputPort->text().toInt(&validPort);
		ui.buttonStart->setEnabled(validIpAddress && validPort);
	});

	// Called when the button start is clicked
	QObject::connect(ui.buttonStart, &QPushButton::clicked, [=](bool checked) {
		ui.buttonStart->setText(QString("Stop"));
		
		sig_connectAndStart(ui.inputIP->text(), ui.inputPort->text().toInt(nullptr));
	});

	// When we call "sig_receiveData" in the instance of the Worker of this instance, call "slot_receiveData" in this instance
	QObject::connect(&this->worker, &Worker::sig_receiveData, this, &MyWindow::slot_receiveData);
}

void MyWindow::slot_receiveData(inputData input) {
    std::cout << input.buttons << std::endl;
}
