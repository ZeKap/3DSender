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
	// Qt app
	QApplication a(argc, argv);
	// Main Window
	MyWindow w;

	// Display the main window
	w.show();

	// Execute main app
	return a.exec();
}
