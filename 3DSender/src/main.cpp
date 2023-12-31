#include <string.h>
#include <3ds.h>
#include <malloc.h>
#include "printer.hpp"
#include "network.hpp"
#include "input_data.hpp"

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

	inputData old_commands, current_commands;

	// Main loop
	while (aptMainLoop() && !should_exit())
	{
		hidScanInput(); // check for new input
		current_commands.buttons = hidKeysHeld();
		hidCircleRead(&current_commands.circlePad); // get circlePad Position

		if (!(current_commands == old_commands))
		{
			print_connected_header(IP);
			print_keys(current_commands);

			// now it's time to PACK
			// wait before
			// need to edit some functs to git the struct in input
			send_new_inputs_to_client(sock_client_fd, current_commands);

			old_commands = current_commands;
		}

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