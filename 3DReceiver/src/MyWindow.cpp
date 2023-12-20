#include "MyWindow.h"
#include <iostream>
#include <arpa/inet.h>

MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.inputIP, &QLineEdit::textEdited, [=](const QString &ip) {
		char buf[4];
		int validIpAddress = inet_pton(AF_INET, ip.toStdString().c_str(), buf);
		ui.buttonStart->setDisabled(validIpAddress==0);
	});

	QObject::connect(ui.buttonStart, &QPushButton::clicked, [=](bool checked) {
		ui.buttonStart->setText(QString("Stop"));
	});
}
