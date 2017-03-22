/*
 * Player.h
 *
 *  Created on: 2014-09-26
 *      Author: Kaibo Ma
 * Header file for keyboard, contains variables and function declarations
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "altera_up_avalon_ps2.h"
#include "altera_up_ps2_keyboard.h"
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include <string.h>

class Keyboard {

public:

	Keyboard();

	void init();

	void readkey(KB_CODE_TYPE code, alt_u8 buffer, char asci, alt_up_ps2_dev* ps2_buffer);
	alt_u8 storeKey(alt_u8 buffer);

	KB_CODE_TYPE code;
	alt_u8 buffer;
	char asci;
	alt_up_ps2_dev* ps2_buffer;





private:

	alt_up_ps2_dev* init_ps2_buffer();
};
#endif
