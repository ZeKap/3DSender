#include <QApplication>
#include <unistd.h>
#include <iostream>
#include "MyWindow.h"
#include "network.hpp"
#include "input_data.hpp"

#define LENGTH_INPUTS 20

void exitErreur(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	/*
	QApplication a(argc, argv);
	MyWindow w;

	w.show();

	return a.exec();
	*/

	int sock_client = connectTo("192.168.1.99", 8000);
	if(sock_client < 0)
	{
		exitErreur("problem connecting");
	}

	// vars used in loop
	int still_working;
	char inputs[LENGTH_INPUTS];

	while (true)
	{
		// wait for new infos to read and store them;
		still_working = read(sock_client, inputs, sizeof(inputs));
		// exit if error or socket closed
		if (still_working == -1)
			exitErreur("read");
		if (!still_working)
			break;

		std::cout << inputs << std::endl;
	}

	close(sock_client);
	std::cout << "socket closed" << std::endl;
	return 0;
}
