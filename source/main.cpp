#include <string>
#include <cmath>

#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>

#include "fidgspin_png.h"
#include "topscr_png.h"

using namespace std;


int main() {
	// Initialize needed services
	sf2d_init();
	hidInit();

	consoleInit(GFX_TOP, NULL);

	// Create a texture for the fidget spinner
	sf2d_texture* fidgetSpinner = sfil_load_PNG_buffer(fidgspin_png, SF2D_PLACE_RAM);
	// Create a texture for the second meme
	sf2d_texture* topScreen     = sfil_load_PNG_buffer(topscr_png,   SF2D_PLACE_RAM);

	// Speed of the spinner
	static int SPEED = 1.0;

	// Position of the spinner on the screen
	int posx = (320 / 2); //- (fidgetSpinner->width   / 2);
	int posy = (240 / 2); //- (fidgetSpinner->height  / 2);

	// The angle at which the spinner rotates
	float angle = 0.0f;

	// Used for what keys were pressed down this frame
	u32 keyDown;
	// Used for what keys were let go this frame
	u32 keyUp;

	// First coordinate in the current/last touchscreen stroke
	touchPosition firstTouch;
	// Final coordinate in the last touchscreen stroke
	touchPosition lastTouch;

	// Current coordinate being touched on the touch screen
	touchPosition touch;

	// Distance between the starting point of the swipe and the end point
	int touchDistance = 0;



	// Debug console


	// Main loop
	while (aptMainLoop()) {



		// Refresh what controls are being pressed
		hidScanInput();

		// keyDown stores which keys were just pressed as of this frame
		keyDown = hidKeysDown();

		// keyUp stores which keys were just released this frame
		keyUp = hidKeysUp();

		// Stores the first point on the screen the user touches
		// When the touch screen is being touched for the first time we record that coordinate to firstTouch
		if (keyDown & KEY_TOUCH) {
			hidTouchRead(&touch);
			firstTouch = touch;
		}

		// Stores the last point on the screen that the user touches
		// When the touch screen stopped being touched as of this frame we record the last coordinate to lastTouch
		if (keyUp & KEY_TOUCH) {
			lastTouch = touch;
		}

		if (keyDown & KEY_START) {
			// Get us the fuck out of here please
			break;
		}

		// Refresh what point on the screen is being pressed
		hidTouchRead(&touch);

		//printf("X1: %u\nY1: %u\nX2: %u\nY2: %u", firstTouch.px, firstTouch.py, lastTouch.px, lastTouch.py);

		// Get some pythagorean on this know whatta mean
		touchDistance = sqrt( ((lastTouch.px - firstTouch.px) ^ 2) - ((lastTouch.py - firstTouch.py) ^ 2) );
		printf("TOUCH DISTANCE: %d", touchDistance);




		// Draw whatever the fuck that is on the top screen (no 3D)
		//sf2d_start_frame(GFX_TOP, GFX_LEFT);
		//sf2d_draw_texture(topScreen, 0, 0);
		//sf2d_end_frame();

		// Draw the finna spidget on the bottom screen
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture_rotate(fidgetSpinner, posx, posy, angle);
		sf2d_end_frame();

		// Increase the speed of the spinning
		angle = angle + ((SPEED) * touchDistance);

		// touchDistance = 0;

		sf2d_swapbuffers();
	}

	sf2d_free_texture(topScreen);
	sf2d_free_texture(fidgetSpinner);
	sf2d_fini();

	return 0;
}
