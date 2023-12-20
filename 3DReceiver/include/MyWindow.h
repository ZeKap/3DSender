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
	void initThread();
	explicit MyWindow(QWidget *parent = 0);
private:
	Ui::root ui;
	Worker worker;
	QThread workerThread;
signals:
	void connectToIp(const QString &ip, int port);
};

#endif // MYWINDOW_H
