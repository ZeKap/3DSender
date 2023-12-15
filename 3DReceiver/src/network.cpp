#include <sys/socket.h>
#include <arpa/inet.h>
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