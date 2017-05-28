#include <string>

#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>

#include "fidgspin_png.h"
#include "topscr_png.h"

using namespace std;

int main() {
	sf2d_init();
	sf2d_texture* fidgetSpinner = sfil_load_PNG_buffer(fidgspin_png, SF2D_PLACE_RAM);
	sf2d_texture* topScreen     = sfil_load_PNG_buffer(topscr_png,   SF2D_PLACE_RAM);

	int posx = (320 / 2); //- (fidgetSpinner->width   / 2);
	int posy = (240 / 2); //- (fidgetSpinner->height  / 2);

	bool spinning = false;
	float angle = 0.0f;

	// Main loop
	while (aptMainLoop()) {
		hidScanInput();
		u32 kDown = hidKeysDown();

		if (kDown & KEY_TOUCH) {
			spinning = (!spinning);
		}

		if (kDown & KEY_START) {
			break;
		}

		// draw instructions
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		sf2d_draw_texture(topScreen, 0, 0);
		sf2d_end_frame();		

		// draw the spidget finner
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		sf2d_draw_texture_rotate(fidgetSpinner, posx, posy, angle);
		sf2d_end_frame();

		// increase the angle, if applicable
		if (spinning) {
			angle = angle + 0.2;
		}

		sf2d_swapbuffers();
	}

	sf2d_free_texture(topScreen);
	sf2d_free_texture(fidgetSpinner);
	sf2d_fini();

	return 0;
}
