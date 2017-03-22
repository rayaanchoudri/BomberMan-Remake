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

Player::Player() { //constructor creates player

	//initialises position and health
	life = 3;
	x_cord = 0;
	y_cord = 0;
	num_bombs = 2;
	for (int i = 0; i < 5; i++) {
		bombs[i].init();
	}

	//initialises parallel port to read from direction from keys
	parallel_port_dev = alt_up_parallel_port_open_dev("/dev/parallel_port_0");
	if (parallel_port_dev == NULL)
		printf("Error: could not open Parallel Port device\n");
	else
		printf("Opened Parallel Port device\n");
}
Player::Player(int x, int y, int player_num) {
	life = 3;
	x_cord = x;
	y_cord = y;
	num_bombs = 2;
	for (int i = 0; i < 5; i++) {
		bombs[i].init();
	}

	parallel_port_dev = alt_up_parallel_port_open_dev("/dev/parallel_port_0");
	if (parallel_port_dev == NULL)
		printf("Error: could not open Parallel Port device\n");
	else
		printf("Opened Parallel Port device\n");
}

void Player::init(int x, int y) {
	life = 3;
	x_cord = x;
	y_cord = y;
	num_bombs = 2;
	bomb_key_pressed = false;
	for (int i = 0; i < 5; i++) {
		bombs[i].init();
	}
	for (int i = 0; i < 5; i++) {
		bombs[i].damaged_blocks.clear();
	}
}

char Player::get_direction(int whichplayer, Keyboard &keyboard) { //returns the direction pressed
	unsigned int key;
	key = alt_up_parallel_port_read_data(parallel_port_dev);
	if (whichplayer == 1) {
		char dir = keyboard.readkey();
		if (dir == 'B'){
			bomb_key_pressed = true;
			return STAND;
		}
		else
			return dir;
	} else {
		if (key != 0) {
			switch (key) {
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
	}
	return STAND;

}

bool Player::move(char direction, MatrixMap& m, unsigned long rand_seed) { //moves in direction pressed if legal
	//checks matrix map for x's marked as legal areas
	x_old_cord = x_cord;
	y_old_cord = y_cord;
	if (direction == UP && m.get_cord(x_cord, y_cord - 1) == 'x' && y_cord > 0)
		move_up();
	else if (direction == DOWN && m.get_cord(x_cord, y_cord + 1) == 'x'
			&& y_cord < SIZE - 1)
		move_down();
	else if (direction == RIGHT && m.get_cord(x_cord + 1, y_cord) == 'x'
			&& x_cord < SIZE - 1)
		move_right();
	else if (direction == LEFT && m.get_cord(x_cord - 1, y_cord) == 'x'
			&& x_cord > 0)
		move_left();

	// checks for power up
	srand(rand_seed);
	for (int i = 0; i < m.powerups.size(); i += 2) {
		if (x_cord == m.powerups[i] && y_cord == m.powerups[i + 1]) {
			m.powerups[i] = -10;
			m.powerups[i + 1] = -10;
			int rand_number = rand() % 10;
			if (rand_number % 2 == 1) {
				printf("POWER UP: %d RANGE++\n", rand_number);
				for (int i = 0; i < 5; i++) {
					bombs[i].power_up_range();
				}
			} else if (rand_number != 0) {
				printf("POWER UP: %d BOMB++\n", rand_number);
				if (num_bombs < 5) {
					num_bombs++;
				}
			} else {
				printf("POWER UP: %d LIFE++\n", rand_number);
				if (life < 5) {
					life++;
				}
			}
//			for (int j = 0; j < m.powerups.size(); j += 2) {
//				printf("x: %d, y:%d\n", m.powerups[j], m.powerups[j + 1]);
//			}
			return true;
		}
	}

	return false;
}

//move functions increment or decrement x or y coordinates
void Player::move_right() {
	x_cord++;
}
void Player::move_left() {
	x_cord--;
}
void Player::move_up() {
	y_cord--;
}
void Player::move_down() {
	y_cord++;
}

//getters return x, y coordinates
int Player::get_x_cord() {
	return x_cord;
}
int Player::get_y_cord() {
	return y_cord;
}

int Player::get_old_x_cord() {
	return x_old_cord;
}

int Player::get_old_y_cord() {
	return y_old_cord;
}

void Player::life_down() {
	life--;
	printf("LIFE DOWN! \n");
	if (life == 0) {
		printf("PLAYER HAS DIED \n");
	}
}

bool Player::check_damage(std::vector<int> &damaged_blocks) {
	for (int i = 0; i < damaged_blocks.size(); i += 2) {
		if (x_cord == damaged_blocks[i] && y_cord == damaged_blocks[i + 1]) {
			this->life_down();
			return true;
		}
	}
	return false;
}

void Player::place_bomb(int player_num, MatrixMap& m, Keyboard &keyboard) {
	if (player_num == 2) {
		if (IORD_8DIRECT(SWITCHES, 0) % 2 == 1) {
			for (int i = 0; i < num_bombs; i++) {
				if (m.map[x_cord][y_cord] != BOMB) {
					if (bombs[i].place_bomb(x_cord, y_cord)) {
						m.map[x_cord][y_cord] = BOMB;
						return;
					}
				}
			}
		}
	} else if (player_num == 1) {
		if (bomb_key_pressed == true) {
			bomb_key_pressed = false;
			for (int i = 0; i < num_bombs; i++) {
				if (m.map[x_cord][y_cord] != BOMB) {
					if (bombs[i].place_bomb(x_cord, y_cord)) {
						m.map[x_cord][y_cord] = BOMB;
						return;
					}
				}
			}
		}
	}
}


int Player::get_life() {
return life;
}

int Player::get_num_bombs() {
return num_bombs;
}
