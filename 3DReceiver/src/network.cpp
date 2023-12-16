#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "network.hpp"

int connectTo(const char *ipAdress, int port)
{
	// prepare socket on host to connect to server later
	int sock_client = socket(AF_INET, SOCK_STREAM, 0);
	// create struct of server to connect
	struct sockaddr_in sockaddr_serveur;
	sockaddr_serveur.sin_family = AF_INET;
	inet_aton(ipAdress, &sockaddr_serveur.sin_addr);
	sockaddr_serveur.sin_port = htons(port);

	// try to connect
	if (connect(sock_client, (struct sockaddr *)&sockaddr_serveur, sizeof(sockaddr_serveur)) == -1)
		return -1;

	return sock_client;
}

int getInputs(int socket, inputData *inputs)
{
#define readOrReturn(var, size)    \
	ok = read(socket, &var, size); \
	if (ok <= 0)                   \
	return ok

	// var to store state of every read
	int ok;

	// wait for new infos to read and store them;
	readOrReturn(inputs->buttons, 4);
	readOrReturn(inputs->circlePad.dx, 2);
	readOrReturn(inputs->circlePad.dy, 2);
	readOrReturn(inputs->accelerometer.x, 2);
	readOrReturn(inputs->accelerometer.y, 2);
	readOrReturn(inputs->accelerometer.z, 2);
	readOrReturn(inputs->gyro.x, 2);
	readOrReturn(inputs->gyro.y, 2);
	readOrReturn(inputs->gyro.z, 2);

	return 1;
}