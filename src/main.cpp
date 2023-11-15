#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include "printer.hpp"

int main()
{
	gfxInitDefault();
	//gfxSet3D(true); //Uncomment if using stereoscopic 3D
	consoleInit(GFX_TOP, NULL); //Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.
	size_t i = 0;

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		//Your code goes here
		print_line(1, 2, "Hello world!");

		print_line(2, 2, "Frame: %d", i++);
		print_line(3, 2, "Press START to exit.");

		u32 kDown = hidKeysHeld();
		print_line(4, 2, "Keys code held: %ld", kDown);

		

		//if (kDown & KEY_START)
		//	break; //Break in order to return to hbmenu // it also break citra

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}