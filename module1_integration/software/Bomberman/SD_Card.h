/*
 * SD_Card.h
 *
 *  Created on: Oct 7, 2014
 *      Author: Emmett
 */

#ifndef SD_CARD_H_
#define SD_CARD_H_

#define BMan_F0 "Bman_F0.bmp"

#define BMan_F3 "Bman_F3.bmp"


#define BMan_B0 "Bman_B0.bmp"

#define BMan_B3 "Bman_B3.bmp"

#define BMan_R0 "Bman_R0.bmp"

#define BMan_R3 "Bman_R3.bmp"

#define BMan_L0 "Bman_L0.bmp"

#define BMan_L3 "Bman_L3.bmp"


#define Rman2_F0 "Rman_F0.bmp"

#define Rman2_F3 "Rman_F3.bmp"


#define Rman2_B0 "Rman_B1.bmp"

#define Rman2_B3 "Rman_B3.bmp"


#define Rman2_R0 "Rman_R0.bmp"

#define Rman2_R3 "Rman_R3.bmp"

#define Rman2_L0 "Rman_L0.bmp"

#define Rman2_L3 "Rman_L3.bmp"


#define Path "path.bmp"
#define Destr_Block "block.bmp"
#define Solid_Block "block2.bmp"
#define Bomb_Map "bomb2.bmp"
#define Speed_Powerup_Bitmap "SpeedUp.bmp"
// Powerup
//#define Speed_Powerup_Bitmap "SpeedUp.bmp"
// Flame
#define Flame_Bitmap "b_f.bmp"

#include "altera_up_sd_card_avalon_interface.h"
#include <vector>
class SD_Card {
public:
	void scan_sd_card(char *directory, char *filename);
	bool init();
	void look_for_other_files(char *filename);
	void setup_bitmaps_from_sd_card();

	short int bomb_Bmap[20][20];

	short int solid_block[20][20];
	short int destr_block[20][20];
	short int path[20][20];

	short int forward[5][20][20];

	short int right[5][20][20];

	short int left[5][20][20];

	short int back[5][20][20];


	short int Rforward[5][20][20];

	short int Rright[5][20][20];

	short int Rleft[5][20][20];

	short int Rback[5][20][20];


	// Powerup Arrays
	short int speed_powerup_array[20][20];

	// Flame Arrays
	short int flame_array[20][20];

	alt_up_sd_card_dev *device_reference;
	int connected;
	char *filename;
	char *directory; // root directory
private:

	void change_bitmap_array_from_file(char* filename,
			short int bitmap_array[20][20]);

};

#endif /* SD_CARD_H_ */
