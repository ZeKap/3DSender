#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <arpa/inet.h>

#include "ui_template.h"

class MyWindow : public QWidget
{
	Q_OBJECT
public:
	explicit MyWindow(QWidget *parent = 0);

private:
	Ui::root ui;
};

#endif // MYWINDOW_H
