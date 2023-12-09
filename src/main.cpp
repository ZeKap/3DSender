#include <string.h>
#include <3ds.h>
#include "printer.hpp"
#include "network.hpp"


int main()
{
	gfxInitDefault();
	//gfxSet3D(true); //Uncomment if using stereoscopic 3D
	consoleInit(GFX_TOP, NULL); //Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.
	
	size_t frames = 0;
	size_t selected = 0;

	acInit();

	je_fonctionne();

	// Main loop
	while (aptMainLoop())
	{
		frames++;
		gspWaitForVBlank();
		hidScanInput();

		//Your code goes here
		print(1, 0, "Hello world!");

		print(2, 0, "Frame: %d", frames);
		print(3, 0, "Press START to exit.");
		print(4, 0, "Selected: %ld", selected);
		print(7, 0, "---------------------");

		print(8, 2, "%c Option 1", selected == 0 ? '>' : ' ');
		print(9, 2, "%c Option 2", selected == 1 ? '>' : ' ');
		print(10, 2, "%c Option 3", selected == 2 ? '>' : ' ');
		print(11, 2, "%c Option 4", selected == 3 ? '>' : ' ');

		u32 kpressed = hidKeysDown();

		if (kpressed & KEY_UP)
			selected = (selected - 1) % 4;
		else if (kpressed & KEY_DOWN)
			selected = (selected + 1) % 4;

		if (kpressed & KEY_START)
			break; //Break in order to return to hbmenu // it also break citra

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}