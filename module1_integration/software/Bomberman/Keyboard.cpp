/*
 * MatrixMap.cpp
 *
 *  Created on: 2014-09-26
 *      Author: Kaibo Ma
 *
 *      Functions that initialize and use the ps2 controller as a keyboard
 */
#include "Keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_ps2_keyboard2.h"

#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'
#define STAND 'S'

Keyboard::Keyboard() {
	printf("Initializing ps2 buffer \n");
	this->ps2_buffer = init_ps2_buffer();

}

alt_up_ps2_dev* Keyboard::init_ps2_buffer() {
	printf("Initializing ps2 Buffer \n");
	alt_up_ps2_dev* ps2_buffer_temp;
	ps2_buffer_temp = alt_up_ps2_open_dev(PS2_0_NAME);
	alt_up_ps2_init(ps2_buffer_temp);
	return ps2_buffer_temp;
}

void Keyboard::init() {
	printf("Initializing Keyboard \n");
	if (this->ps2_buffer->device_type == PS2_MOUSE) {
		printf("Error Initializing ps2 buffer. \n");
		return;
	} else if (this->ps2_buffer->device_type == PS2_KEYBOARD) {
		printf("Initialized as Keyboard...\n");
	} else if (this->ps2_buffer->device_type == PS2_UNKNOWN) {
		printf("Initialized as Unknown...\n");
	}
}

char Keyboard::readkey() {
	int tempdecode;
	tempdecode = decode_scancode(ps2_buffer, &code, &buffer, &asci);

	if (tempdecode == 0) {
		//printf("test\n");
		//printf("test: %hhx \n", buffer);
		if (code == 0x1) {
			//if (whichplayer == 1) {
				//if (code == 0x1) {
				//	printf("%x \n", code);
				if (buffer == 0x1d) {
					//printf("W is pressed \n");
					//printf("%hhx \n", buffer);
					return UP;
				} else if (buffer == 0x1b) {
					//printf("S is pressed \n");
					//printf("%hhx \n", buffer);
					return DOWN;
				} else if (buffer == 0x1c) {
					//printf("A is pressed \n");
					//printf("%hhx \n", buffer);
					return LEFT;
				} else if (buffer == 0x23) {
					//printf("D is pressed \n");
					//printf("%hhx \n", buffer);
					return RIGHT;
				} else if (buffer == 0x32) {
					//printf("B is pressed \n");
					//printf("%hhx \n", buffer);
					return 'B';
				}
			//}
			/*else if (whichplayer == 2) {
				//if (code == 0x1) {
				if (buffer == 0x75) {
					printf("8(up) is pressed \n");
					printf("%hhx \n", buffer);
					return UP;
				} else if (buffer == 0x6b) {
					printf("4(left) is pressed \n");
					printf("%hhx \n", buffer);
					return LEFT;
				} else if (buffer == 0x74) {
					printf("6(right) is pressed \n");
					printf("%hhx \n", buffer);
					return RIGHT;
				} else if (buffer == 0x73) {
					printf("2(down) is pressed \n");
					printf("%hhx \n", buffer);
					return DOWN;
				} else if (buffer == 0x70) {
					printf("0(bomb) is pressed \n");
					printf("%hhx \n", buffer);
				}
			}*/
		}
	}
	return STAND;
}
