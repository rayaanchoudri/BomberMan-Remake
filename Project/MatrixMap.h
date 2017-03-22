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
#define SIZE 11

class MatrixMap{//creates matrix representation of map
	private:
		char map[SIZE][SIZE];
		//int nrows, ncols;

		//char* gen_map();

	public:
		MatrixMap();
		MatrixMap(int nrows, int ncols);
		void gen_map();
		void print_matrix();
		void printrow_x();
		void printrow_y();
		char** get_map();
		char get_cord(int x, int y);
};

#endif /* MATRIXMAP_H_ */
