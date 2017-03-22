#include <stdio.h>
#include <string.h>
#include "io.h"
#include <stdlib.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "VGA_Screen.h"

using namespace std;
int main() {
	VGA_Screen vga_screen;
	vga_screen.init();
	vga_screen.clear_screen(vga_screen.pixel_buffer);
	vga_screen.draw_map_from_array();
}
