/*
 * MatrixMap.h
 *
 *  Created on: 2014-09-26
 *      Author: Rayaan Choudri/ Lucas Gomes
 *      matrix representation of map, marks walkable pixels as x and nonwalkable as o
 */

#ifndef MATRIXMAP_H_
#define MATRIXMAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "VGA_Screen.h"
#include <vector>

#define SIZE 11

#define PATH 'x'
#define BLOCK 'o' //indestructible
#define BOX 'a' //destructible
#define BOMB 'b'

class MatrixMap{//creates matrix representation of map
	private:

	public:

		char map[SIZE][SIZE];
		MatrixMap();
		MatrixMap(int nrows, int ncols);
		void gen_map(unsigned long rand_cicles );
		void print_matrix();
		void printrow_x();
		void printrow_y();
		char get_cord(int x, int y);
		void check_explosion(int x, int y, VGA_Screen& vga);
		std::vector<int> check_damaged_blocks(int x, int y, int range, std::vector<int> &damaged_blocks, unsigned long rand_seed);
		std::vector<int> powerups;
};

#endif /* MATRIXMAP_H_ */
