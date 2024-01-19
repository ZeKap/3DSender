#include <QApplication>
#include <unistd.h>
#include <iostream>
#include "MyWindow.h"
#include "network.hpp"
#include "input_data.hpp"

void exitErreur(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyWindow w;

	w.show();

	return a.exec();
}
