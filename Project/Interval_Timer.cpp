/*
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "sys/alt_timestamp.h"
#include <iostream>
#include "altera_up_avalon_character_lcd.h"
#include <time.h>
#include "Player.h"
#include "MatrixMap.h"
#include "unistd.h"

void wait(int seconds);
int main()
{
   //init arrays and var
	  int x, y;
	  int a[100][100];
	  int b[100][100];
	  int c[100][100];
	  int i, j, k;
	  int sum;
	  int start_time;
	  int end_time;
	  float freq;

	  Player p;
	  MatrixMap m;
	  m.print_matrix();

	  while(1){
		  p.move(p.get_direction(), m);
		  printf("%c\n", p.get_direction());
		  printf("x = %d   y = %d	cord=%c\n", p.get_x_cord(), p.get_y_cord(), m.get_cord(p.get_x_cord(), p.get_y_cord()));
		  usleep(100000);
	  }
  //for random num generation
	 /* srand(time(NULL));

  	  //init lcd and random message to test
  	  const char* yala = "Yala Habibi!";
  	  alt_up_character_lcd_dev* d = alt_up_character_lcd_open_dev("/dev/character_lcd_0");
  	  alt_up_character_lcd_init(d);
  	  alt_up_character_lcd_string(d, yala);

  	  //random 100x100 matrix gen
	  for(x = 0; x < 100; x++) {
		  for(y = 0; y < 100; y++)
			  a[x][y] = rand();
	  }
	  for(x = 0; x < 100; x++) {
			for(y = 0; y < 100; y++)
				b[x][y] = rand();
		}

	  // Interval Timer for 100x100 matrix multiplication
	  freq=alt_timestamp_freq();

	  alt_timestamp_start();
	  for(i= 0; i < 100; i++) {
			for(j= 0; j < 100; j++){
				sum = 0;
				for (k=0; k<100; k++){
					sum = sum + a[i][k] * b[k][j];
				}
				c[i][j]= sum;
			}
		}
	  end_time=alt_timestamp();

	  float sec= end_time/freq;
	  printf("Time taken: %d clock ticks\n", end_time);
	  printf("            %f seconds\n", sec );*/
	  return 0;
}
void wait ( int seconds )
{
	clock_t endwait;
	endwait = clock () + seconds * CLOCKS_PER_SEC ;
	while (clock() < endwait) {}
}
