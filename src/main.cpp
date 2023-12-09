#include <string.h>
#include <3ds.h>
#include <malloc.h>
#include "printer.hpp"
#include "network.hpp"


void print_stuff_to_screen(u32 kpressed, char* IP) {
	static size_t frames = 0;
	static size_t selected = 0;

	if (kpressed & KEY_UP) {
		selected = (selected - 1) % 4;
	} else if (kpressed & KEY_DOWN) {
		selected = (selected + 1) % 4;
	}

	print(1, 0, "Hello world!");

	print(2, 0, "Frame: %d", frames);
	print(3, 0, "Press START to exit.");
	print(4, 0, "Selected: %ld", selected);
	print(5, 0, "IP: %s", IP);
	print(7, 0, "---------------------");

	print(8, 2, "%c Option 1", selected == 0 ? '>' : ' ');
	print(9, 2, "%c Option 2", selected == 1 ? '>' : ' ');
	print(10, 2, "%c Option 3", selected == 2 ? '>' : ' ');
	print(11, 2, "%c Option 4", selected == 3 ? '>' : ' ');

	frames++;
}

// returns true if we should exit
bool should_exit() {
	u32 kpressed = hidKeysDown();
	
	//Break in order to return to hbmenu // it also break citra
	if (kpressed & KEY_START) {
		return true;
	}
	return false;
}

int main()
{
	gfxInitDefault();
	//gfxSet3D(true); //Uncomment if using stereoscopic 3D
	consoleInit(GFX_TOP, NULL); //Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.

	auto res = init_network();
	if (res != 0) {
		print(6, 0, "Network init failed: %i", res);
	}

	char * IP = test_get_IP();

	// Main loop
	while (aptMainLoop() && !should_exit())
	{
		hidScanInput(); // check for new input
		u32 kpressed = hidKeysDown(); // get input

		print_stuff_to_screen(kpressed, IP);

		gspWaitForVBlank(); // frame limiter

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}