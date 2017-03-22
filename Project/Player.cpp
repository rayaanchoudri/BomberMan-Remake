/*
 * Player.c
 *
 *  Created on: 2014-09-26
 *  Author: Rayaan Choudri
 *
 *  Contains player movement functions and variables
 */
#include "Player.h"
#include "MatrixMap.h"

	Player::Player(){//constructor creates player

		 //initialises position and health
		 health = 3;
		 x_cord = 0;
		 y_cord = 0;

		 //initialises parallel port to read from direction from keys
		 parallel_port_dev = alt_up_parallel_port_open_dev("/dev/parallel_port_0");
			 if (parallel_port_dev == NULL)
					printf("Error: could not open Parallel Port device\n");
				 else
					printf("Opened Parallel Port device\n");
	}

	char Player::get_direction(){//returns the direction pressed
		unsigned int key;
		key = alt_up_parallel_port_read_data(parallel_port_dev);

			if (key != 0){
				switch(key){
					case 1:
						return RIGHT;
						break;
					case 2:
						return LEFT;
						break;
					case 4:
						return DOWN;
						break;
					case 8:
						return UP;
						break;
						}
					}
			return STAND;
		}

	void Player::move(char direction, MatrixMap& m){//moves in direction pressed if legal
		//checks matrix map for x's marked as legal areas

			if(direction == UP && m.get_cord(x_cord, y_cord-1)=='x' && y_cord>0)
					move_up();
			else if(direction == DOWN && m.get_cord(x_cord, y_cord+1)=='x' && y_cord<SIZE-1)
					move_down();
			else if(direction == RIGHT && m.get_cord(x_cord+1, y_cord)=='x' && x_cord<SIZE-1)
					move_right();
			else if(direction == LEFT && m.get_cord(x_cord-1, y_cord)=='x' && x_cord>0)
					move_left();
	}

	//move functions increment or decrement x or y coordinates
	void Player::move_right(){
			printf("Moving right...");
			x_cord++;
	}
	void Player::move_left(){
			printf("Moving left...");
			x_cord--;
	}
	void Player::move_up(){
			printf("Moving up...");
			y_cord--;
	}
	void Player::move_down(){
			printf("Moving down...");
			y_cord++;
	}

	//getters return x, y coordinates
	int Player::get_x_cord(){
		return x_cord;
	}
	int Player::get_y_cord(){
		return y_cord;
	}


