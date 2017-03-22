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

	//char m = new map[SIZE][SIZE];
	gen_map();

}

MatrixMap::MatrixMap(int rows, int cols) { //future contructor
	/*nrows = rows;
	 ncols = cols;
	 m = new map[nrows][ncols];
	 gen_map();*/
}

void MatrixMap::gen_map() { //generates map
	//int i, j, k;

	for (int i = 0; i < SIZE; i++) {

		for (int j = 0; j < SIZE; j++) {
			if (i % 2 == 0)
				map[i][j] = 'x';
			else {
				if (j % 2 == 0) {

					map[i][j] = 'x';
				} else
					map[i][j] = 'o';
			}
		}

	}

}
char MatrixMap::get_cord(int x, int y) {
	return map[x][y];
}
void MatrixMap::print_matrix() { //prints map to screen
	int i, j, k;

	for (i = 0; i < SIZE; i++) {

		for (j = 0; j < SIZE; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}

}
