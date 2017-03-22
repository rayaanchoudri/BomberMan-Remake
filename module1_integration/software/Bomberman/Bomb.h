/*
 * Bomb.h
 *
 *  Created on: 2014-10-01
 *      Author: Lucas
 */

#ifndef BOMB_H_
#define BOMB_H_


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>

#define EXPLOSION_TIME 70
#define EXPLOSION_ANIMATION_DELAY 10

class Bomb{
	private:
		bool active;
		int timer;
		int x_cord;
		int y_cord;
		int explosion_range; // MIN 2, MAX 5

		int explosion_animation_timer;
		bool in_explosion;
	public:
		Bomb();
		bool isActive();
		bool place_bomb(int x_cord, int y_cord);
		bool exploded();
		int get_x_cord();
		int get_y_cord();
		void increment_timer();
		int get_explosion_range();
		std::vector<int> damaged_blocks;
		void init();
		void power_up_range();

		bool isExploding();
		bool finishedExploding();
};



#endif /* BOMB_H_ */
