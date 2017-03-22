/*
 * Game.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Emmett
 */

#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <string.h>
#include "io.h"
#include <stdlib.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include <time.h>
#include "sys/alt_timestamp.h"
#include <iostream>
#include "MatrixMap.h"
#include "VGA_Screen.h"
#include "Player.h"
#include "unistd.h"
#include "altera_up_sd_card_avalon_interface.h"
#include "SD_Card.h"
#include <string>
#include <sstream>
#include "Keyboard.h"
#include "Audio.h"

class Game {
public:
	Player player1;
	Player player2;
	MatrixMap matrix_map;
	VGA_Screen vga_screen;
	SD_Card sd_card;
	Keyboard keyboard;
	Audio game_audio;

	bool game_over;

	Game();

	void init();

	void draw_map_and_player();

	void menu_screen();

	void match_start();

	void game_logic(Player &player1, Player &player2, MatrixMap &matrix_map,
			VGA_Screen &vga_screen);
	void game_drawing(Player &player1, Player &player2, MatrixMap &matrix_map,
			VGA_Screen &vga_screen);


	void run();
};

#endif /* GAME_H_ */
