/*
 * VGA_Screen.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: Emmett
 */

#include "VGA_Screen.h"

// Constructor
VGA_Screen::VGA_Screen() {
	printf("Constructing VGA Screen \n");
	this->pixel_buffer = init_pixel_buffer();
	this->char_buffer = init_char_buffer();
}

// Make sure you call this when creating a VGA_Screen object
void VGA_Screen::init() {
	// Init Screen
	printf("Initializing VGA Screen \n");
	if (this->pixel_buffer == 0) {
		printf(
				"error initializing pixel buffer (check name in alt_up_pixel_buffer_dma_open_dev)\n");
		return;
	}
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
			PIXEL_BUFFER_BASE);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer))
		;
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

	// TODO erase this when kaibo done integrating files together
	this->init_array();
}

// TODO Draw a character, needs to take in input
void VGA_Screen::draw_character(alt_up_char_buffer_dev* char_buffer) {
	printf("Drawing Character \n");
	alt_up_char_buffer_string(char_buffer, "Swag", 10, 120);
	alt_up_char_buffer_string(char_buffer, "Swag", 310, 120);
}

// Not sure if this will be useful or not, but kept it anyways
void VGA_Screen::draw_diagonal_line(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	printf("Drawing Diagonal Line \n");
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 0, 0, 320, 240, 0x00ff, 0);
}

//
void VGA_Screen::draw_boxes(alt_up_pixel_buffer_dma_dev* pixel_buffer, int x_0,
		int x_1, int y_0, int y_1, int color) {
	printf("Drawing Box \n");
	IOWR_32DIRECT(drawer_base, 0, x_0);
	// Set x1
	IOWR_32DIRECT(drawer_base, 4, y_0);
	// Set y1
	IOWR_32DIRECT(drawer_base, 8, x_1);
	// Set x2
	IOWR_32DIRECT(drawer_base, 12, y_1);
	// Set y2
	IOWR_32DIRECT(drawer_base, 16, color);
	// Set colour
	IOWR_32DIRECT(drawer_base, 20, 1);
	// Start drawing
	while (IORD_32DIRECT(drawer_base,20) == 0)
		; // wait until done
}

// paints screen black, you can change color in coding
void VGA_Screen::paint_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	printf("Painting Screen White \n");
	IOWR_32DIRECT(drawer_base, 0, 0);
	// Set x1
	IOWR_32DIRECT(drawer_base, 4, 0);
	// Set y1
	IOWR_32DIRECT(drawer_base, 8, 320);
	// Set x2
	IOWR_32DIRECT(drawer_base, 12, 240);
	// Set y2
	IOWR_32DIRECT(drawer_base, 16, 0x0000);
	// Set colour
	IOWR_32DIRECT(drawer_base, 20, 1);
	// Start drawing
	while (IORD_32DIRECT(drawer_base,20) == 0)
		; // wait until done
}

// Clears screen. Can't clear characters, needs to be checked out
void VGA_Screen::clear_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	printf("Clearing Screen \n");
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

}

//Private Methods. Does not need to be changed, called by the init() function
alt_up_pixel_buffer_dma_dev* VGA_Screen::init_pixel_buffer() {
	printf("Initializing Pixel Buffer \n");
	alt_up_pixel_buffer_dma_dev* pixel_buffer_temp =
			alt_up_pixel_buffer_dma_open_dev("/dev/buffer_dma");
	return pixel_buffer_temp;
}

alt_up_char_buffer_dev* VGA_Screen::init_char_buffer() {
	printf("Initializing Char Buffer \n");
	alt_up_char_buffer_dev* char_buffer;
	char_buffer = alt_up_char_buffer_open_dev(
			"/dev/video_character_buffer_with_dma_0");
	alt_up_char_buffer_init(char_buffer);
	return char_buffer;

}

//high level drawing stuff

//taking in array
void VGA_Screen::draw_map_from_array() {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			this->draw_box_from_coordinate(i,j,map[i][j]);
		}
	}
}

// Drawing 20x20 box: takes in top left coordinate of box
void VGA_Screen::draw_box_from_coordinate(int x, int y, char c){
	int x_scaled = x*20 + 50;
	int y_scaled = y*20 + 10;
	int color;
	if (c == 'o'){
		color = 0xFF8F;
	}
	else if(c == 'x') {
		color = 0xFF4500;
	}
	else{
		printf("check your character array, something is wrong");
		return;
	}
	this->draw_boxes(this->pixel_buffer, x_scaled, x_scaled+20, y_scaled, y_scaled+20, color);
}

// Erase this when done
void VGA_Screen::init_array() {
	for (int i = 0; i < 11; i++) {

		for (int j = 0; j < 11; j++) {
			if (i % 2 == 0) {
				map[i][j] = 'x';
			} else {
				if (j % 2 == 0) {

					map[i][j] = 'x';
				} else{
					map[i][j] = 'o';
				}
			}
		}

	}
}
