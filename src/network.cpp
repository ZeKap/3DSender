#include "network.hpp"
#include <string.h>
#include <malloc.h>
#include <poll.h>

#define MAX_CONNECTIONS 5
#define PORT 8000

Result init_network()
{
     Result res;
     res = acInit();
     if (res != 0)
     {
          return res;
     }

     res = socInit((u32 *)memalign(0x1000, 0x100000), 0x100000);
     if (res != 0)
     {
          return res;
     }

     return 0;
}

int launch_server()
{
     // ipv4, tcp, (tkt)
     int sock_server = socket(AF_INET, SOCK_STREAM, 0);

     // params de sock_server
     struct sockaddr_in sockaddr_server;

     sockaddr_server.sin_family = AF_INET;                // ipv4
     sockaddr_server.sin_port = htons(PORT);              // port 80 (convertis en binaire avec htons)
     sockaddr_server.sin_addr.s_addr = htonl(INADDR_ANY); // ip qui écoute (tous pour être sûr que la 3DS a son IP)

     int yes = 1;
     int close_at_end = setsockopt(sock_server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
     if (close_at_end == -1)
     {
          println(0, "T'as fait de la merde: close_at_end");
          println(0, "Avec errno %d", errno);
     }

     int bind_working = bind(sock_server, (struct sockaddr *)&sockaddr_server, sizeof(sockaddr_in));
     if (bind_working == -1)
     {
          println(0, "T'as fait de la merde: bind_working");
          println(0, "Avec errno %d", errno);
     }

     int listen_working = listen(sock_server, MAX_CONNECTIONS);
     if (listen_working == -1)
     {
          println(0, "T'as fait de la merde: listen_working");
          println(0, "Avec errno %d", errno);
     }

     //println(0, "Le serveur écoute sur le port %d", PORT);

     return sock_server;
}

int accept_client(int sock_server)
{
     // socket client pour parler
     struct sockaddr_in sockaddr_client;
     socklen_t size = sizeof(sockaddr_client);

     // accepte la connexion du client
     int sock_client = accept(sock_server, (struct sockaddr *)&sockaddr_client, &size);
     if (sock_client == -1)
     {
          println(0, "T'as fait de la merde: sock_client");
          println(0, "Avec errno %d", errno);
     }

     return sock_client;
}

bool read_client_msg(int sock_client)
{
     char buffer[256];
     int bytes_read = read(sock_client, buffer, 256 - 1);
     if (bytes_read == -1)
     { // error
          return false;
     }
     else if (bytes_read == 0)
     { // connection finished
          return false;
     }
     else
     {
          buffer[bytes_read] = 0;
          println(6, "Message: %s", buffer);
          return true;
     }
}

bool write_client_msg(int sock_client, const void *data, size_t size)
{
     int written_bytes = write(sock_client, data, size);
     if (written_bytes == -1)
     {
          return false;
     }
     else if ((size_t)written_bytes != size)
     {
          return false;
     }
     else
     {
          return true;
     }
}

char *get_IP()
{
     long lIP = gethostid();

     // create an in_addr struct (that contains the address)
     in_addr an_address;
     // set its s_addr field to the IP
     an_address.s_addr = lIP;
     // get the string representation from the struct
     char *strIP = inet_ntoa(an_address);

     return strIP;
}
