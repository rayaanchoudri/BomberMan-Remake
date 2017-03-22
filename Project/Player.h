/*
 * Player.h
 *
 *  Created on: 2014-09-26
 *      Author: Rayaan Choudri/ Lucas Gomes
 * Header file for player, contains variables and function declarations
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "altera_up_avalon_parallel_port.h"
#include <stdio.h>
#include <stdlib.h>
#include "sys/alt_timestamp.h"
#include <iostream>
#include "altera_up_avalon_character_lcd.h"
#include <time.h>
#include "MatrixMap.h"

#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'
#define STAND 'S'
	class Player {
	private:
	// private variables
		char direction;
		int x_cord;
		int y_cord;
		int health; //3 hit until death
	//private functions
		void move_right();
		void move_left();
		void move_up();
		void move_down();
		void life_down();
		void life_up();

		alt_up_parallel_port_dev* parallel_port_dev;

	public:
		Player();
		bool validate_next_move(char direction);
		char get_direction(); // interrupt, returns l,r,f,b
		int get_x_cord();
		int get_y_cord();
		void move(char direction, MatrixMap& m);




	};


#endif /* PLAYER_H_ */
