#include <QApplication>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include "MyWindow.h"

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

	// prepare socket on host to connect to server later
	int sock_client = socket(AF_INET, SOCK_STREAM, 0);
	// create struct of server to connect
	struct sockaddr_in sockaddr_serveur;
	sockaddr_serveur.sin_family = AF_INET;
	inet_aton("192.168.1.99", &sockaddr_serveur.sin_addr);
	sockaddr_serveur.sin_port = htons(8000);

	// try to connect
	if(connect(sock_client, (struct sockaddr *)&sockaddr_serveur, sizeof(sockaddr_serveur)) == -1)
		exitErreur("connect");

	// vars used in loop
	int still_working;
	char inputs[LENGTH_INPUTS];

	while(true)
	{
		// wait for new infos to read and store them;
		still_working = read(sock_client, inputs, sizeof(inputs));
		// exit if error or socket closed
		if(still_working == -1) exitErreur("read");
		if(!still_working) break;

		std::cout << inputs << std::endl;
	}

	close(sock_client);
	std::cout << "socket closed" << std::endl;
	return 0;
}
