#include <string.h>
#include <stdio.h>
#include <3ds.h>

int main()
{
	gfxInitDefault();
	//gfxSet3D(true); //Uncomment if using stereoscopic 3D
	consoleInit(GFX_TOP, NULL); //Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		//Your code goes here
		printf("\x1b[16;20HHello World!\nPress START to exit.");

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; //Break in order to return to hbmenu

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}