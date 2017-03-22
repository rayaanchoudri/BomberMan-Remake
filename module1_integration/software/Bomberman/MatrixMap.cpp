/*
 * MatrixMap.cpp
 *
 *  Created on: 2014-09-26
 *      Author: Rayaan Choudri
 *
 *      Matrix representation of mao, with x's marked as legal areas and o's as illegal
 */
#include "MatrixMap.h"

MatrixMap::MatrixMap() { //contructor dynamically initializes and generates map

	srand(time(NULL));
	//char m = new map[SIZE][SIZE];
	gen_map(0);

}

MatrixMap::MatrixMap(int rows, int cols) { //future contructor
	/*nrows = rows;
	 ncols = cols;
	 m = new map[nrows][ncols];
	 gen_map();*/
}

char randomize_path() {
	if (rand() % 2 == 0) {
		return BOX;
	} else {
		return PATH;
	}
}

void MatrixMap::gen_map(unsigned long rand_cicles) { //generates map
	//int i, j, k;
	srand(rand_cicles);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (i % 2 == 0)
				map[i][j] = randomize_path();
			else {
				if (j % 2 == 0) {
					map[i][j] = randomize_path();
				} else
					map[i][j] = 'o';
			}
		}
	}

	map[0][0] = PATH;
	map[0][1] = PATH;
	map[1][0] = PATH;
	map[10][10] = PATH;
	map[10][9] = PATH;
	map[9][10] = PATH;

}
char MatrixMap::get_cord(int x, int y) {
	return map[x][y];
}

void MatrixMap::print_matrix() { //prints map to screen
	int i, j;

	for (i = 0; i < SIZE; i++) {

		for (j = 0; j < SIZE; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}

}

void MatrixMap::check_explosion(int x, int y, VGA_Screen& vga) {
	for (int i = x - 2; i < x + 2; i++) {
		if (i >= 0 && i < 11 && map[i][y] == BOX) {
			map[i][y] = PATH;
			vga.clear_bomb(i, y);
		}
	}
	for (int i = y - 2; i < y + 2; i++) {
		if (i >= 0 && i < 11 && map[x][i] == BOX) {
			map[x][i] = PATH;
			vga.clear_bomb(x, i);
		}
	}
	vga.clear_bomb(x, y);
	this->print_matrix();
}

std::vector<int> MatrixMap::check_damaged_blocks(int x, int y, int range, std::vector<int> &damaged_blocks, unsigned long rand_seed) {
	damaged_blocks.clear();
	//this->powerups.clear();
	srand(rand_seed);

	for (int i = x - 1; i >= x - range; i--) {
		if (i >= 0 && (map[i][y] == BOX || map[i][y] == BOMB)) {
			damaged_blocks.push_back(i);
			damaged_blocks.push_back(y);
			if (map[i][y] == BOX) {
				int powerup_rand = rand()%3;
				if (powerup_rand == 0) {
					powerups.push_back(i);
					powerups.push_back(y);
				}
			}
			map[i][y] = PATH;
			break;
		} else if (i < 0 || map[i][y] == BLOCK) {
			break;
		} else if (map[i][y] == PATH) {
			damaged_blocks.push_back(i);
			damaged_blocks.push_back(y);
		}
	}

	for (int i = x + 1; i <= x + range; i++) {
		if (i < 11 && (map[i][y] == BOX || map[i][y] == BOMB)) {
			damaged_blocks.push_back(i);
			damaged_blocks.push_back(y);
			if (map[i][y] == BOX) {
				int powerup_rand = rand()%3;
				if (powerup_rand == 0) {
					powerups.push_back(i);
					powerups.push_back(y);
				}
			}
			map[i][y] = PATH;
			break;
		} else if (i >= 11 || map[i][y] == BLOCK) {
			break;
		} else if (map[i][y] == PATH) {
			damaged_blocks.push_back(i);
			damaged_blocks.push_back(y);
		}
	}

	for (int i = y - 1; i >= y - range; i--) {
		if (i >= 0 && (map[x][i] == BOX || map[x][i] == BOMB)) {
			damaged_blocks.push_back(x);
			damaged_blocks.push_back(i);
			if (map[x][i] == BOX) {
				int powerup_rand = rand()%3;
				if (powerup_rand == 0) {
					powerups.push_back(x);
					powerups.push_back(i);
				}
			}
			map[x][i] = PATH;
			break;
		} else if (i < 0 || map[x][i] == BLOCK) {
			break;
		} else if (map[x][i] == PATH) {
			damaged_blocks.push_back(x);
			damaged_blocks.push_back(i);
		}
	}

	for (int i = y + 1; i <= y + range; i++) {
		if (i < 11 && (map[x][i] == BOX || map[x][i] == BOMB)) {
			damaged_blocks.push_back(x);
			damaged_blocks.push_back(i);
			if (map[x][i] == BOX) {
				int powerup_rand = rand()%3;
				if (powerup_rand == 0) {
					powerups.push_back(x);
					powerups.push_back(i);
				}
			}
			map[x][i] = PATH;
			break;
		} else if (i >= 11 || map[x][i] == BLOCK) {
			break;
		} else if (map[x][i] == PATH) {
			damaged_blocks.push_back(x);
			damaged_blocks.push_back(i);
		}
	}

	damaged_blocks.push_back(x);
	damaged_blocks.push_back(y);
	map[x][y] = PATH;
	return damaged_blocks;
}
