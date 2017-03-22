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
#include <vector>
#include "sys/alt_timestamp.h"
#include <iostream>
#include <time.h>
#include "MatrixMap.h"
#include "Bomb.h"
#include "VGA_Screen.h"
#include "Keyboard.h"

#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'
#define STAND 'S'

#define SWITCHES 0x0002040

class Player {
private:
	// private variables
	char direction;
	int x_cord;
	int y_cord;
	int x_old_cord;
	int y_old_cord;
	int life; //3 hit until death
	bool bomb_key_pressed;

	//private functions
	void move_right();
	void move_left();
	void move_up();
	void move_down();
	void life_up();


	alt_up_parallel_port_dev* parallel_port_dev;

public:
	Player();
	void init(int x, int y);
	Player(int x, int y, int player_num);
	bool validate_next_move(char direction);
	char get_direction(int whichplayer, Keyboard &keyboard); // interrupt, returns l,r,f,b
	int get_x_cord();
	int get_y_cord();
	int get_old_x_cord();
	int get_old_y_cord();
	bool move(char direction, MatrixMap& m, unsigned long rand_seed); // return true if power up
	void life_down();
	bool check_damage(std::vector<int> &damaged_blocks);
	void place_bomb(int player_num, MatrixMap& m, Keyboard &keyboard);
	int get_life();
	int get_num_bombs();
	Bomb bombs[5];
	int num_bombs;
};

#endif /* PLAYER_H_ */
