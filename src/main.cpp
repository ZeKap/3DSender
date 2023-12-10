#include <string.h>
#include <3ds.h>
#include <malloc.h>
#include "printer.hpp"
#include "network.hpp"

void print_connected_header(char *IP)
{
	print(1, 0, "Hello world!");

	print(2, 0, "Press START to exit.");
	print(3, 0, "IP: %s", IP);
}

void print_keys_held(u32 kheld) {
	static u32 last_held = 0;  // store last keys change
	if (kheld != last_held)
	{
		print(4, 0, "                    ");
		print(4,0, "%u", kheld);
		last_held = kheld;
	}
}

// returns true if we should exit
bool should_exit()
{
	u32 kpressed = hidKeysDown();

	// Break in order to return to hbmenu // it also break citra
	if (kpressed & KEY_START)
	{
		return true;
	}
	return false;
}

void send_new_inputs_to_client(int sock_client_fd, u32 kheld)
{
	static u32 last_held = 0;  // store last keys change
	if (kheld != last_held)
	{
		write_client_msg(sock_client_fd, &kheld, 4);
		last_held = kheld;
	}
}

int main()
{
	gfxInitDefault();
	// gfxSet3D(true); //Uncomment if using stereoscopic 3D
	consoleInit(GFX_TOP, NULL); // Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.

	auto res = init_network();
	if (res != 0)
	{
		print(6, 0, "Network init failed: %i", res);
	}

	char *IP = get_IP();
	print(0, 0, "Connect to %s to start", IP);

	int sock_server_fd = launch_server();
	int sock_client_fd = accept_client(sock_server_fd);
	consoleClear();

	// Main loop
	while (aptMainLoop() && !should_exit())
	{
		hidScanInput(); // check for new input
		u32 kheld = hidKeysHeld();

		send_new_inputs_to_client(sock_client_fd, kheld);

		print_connected_header(IP);
		print_keys_held(kheld);

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank(); // frame limiter
	}

	close(sock_client_fd);
	close(sock_server_fd);
	gfxExit();
	return 0;
}