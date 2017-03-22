//#include <stdio.h>
//#include <stdlib.h>
#include "altera_up_avalon_character_lcd.h"
#include "altera_up_avalon_parallel_port.h"


// Do something for the sum!!!!

int main(void)
{
	alt_up_character_lcd_dev * char_lcd_dev;
	alt_up_parallel_port_dev* parallel_port_dev;
	unsigned int key;
	char *key_str;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");
	parallel_port_dev = alt_up_parallel_port_open_dev("/dev/parallel_port_0");

	if ( char_lcd_dev == NULL)
		alt_printf ("Error: could not open character LCD device\n");
	else
		alt_printf ("Opened character LCD device\n");

	if (parallel_port_dev == NULL)
		alt_printf ("Error: could not open Parallel Port device\n");
	else
		alt_printf ("Opened Parallel Port device\n");

	/* Initialize the character display */
	alt_up_character_lcd_init (char_lcd_dev);

	/* Write in the first row */
	alt_up_character_lcd_string(char_lcd_dev, "Keys pressed:");

	while(1){
		key = alt_up_parallel_port_read_data(parallel_port_dev);

		if (key != 0){
			unsigned int mask = 8;
			printf("%d\n", key);/* Write in the second row */

			switch(key){
				case 1:
					key_str = "0      ";
					break;
				case 2:
					key_str = "1      ";
					break;
				case 3:
					key_str = "0 1      ";
					break;
				case 4:
					key_str = "2      ";
					break;
				case 5:
					key_str = "0 2      ";
					break;
				case 6:
					key_str = "1 2      ";
					break;
				case 7:
					key_str = "0 1 2    ";
					break;
				case 8:
					key_str = "3        ";
					break;
				case 9:
					key_str = "0 3      ";
					break;
				case 10:
					key_str = "1 3      ";
					break;
				case 11:
					key_str = "0 1 3    ";
					break;
				case 12:
					key_str = "2 3      ";
					break;
				case 13:
					key_str = "0 2 3    ";
					break;
				case 14:
					key_str = "1 2 3    ";
					break;
				case 15:
					key_str = "0 1 2 3  ";
					break;
			}

			alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
			alt_up_character_lcd_string(char_lcd_dev, key_str);
		}
		else{
			key_str = "             \0";
			alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
			alt_up_character_lcd_string(char_lcd_dev, key_str);
		}
	}

}
