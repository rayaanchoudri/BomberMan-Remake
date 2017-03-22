/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include "sys/alt_timestamp.h"
#include "altera_up_avalon_character_lcd.h"
#include <time.h>
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
  //for random num generation
	  srand(time(NULL));

  	  /*//init lcd and random message to test
  	  const char* yala = "Yala Habibi!";
  	  alt_up_character_lcd_dev* d = alt_up_character_lcd_open_dev("/dev/character_lcd_0");
  	  alt_up_character_lcd_init(d);
  	  alt_up_character_lcd_string(d, yala);*/

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
	  printf("            %f seconds\n", sec );
	  return 0;
}
