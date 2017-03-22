#include <stdio.h>
#include "io.h"
#include <stdlib.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#define drawer_base (volatile int *) 0x2100

int main()
{
	alt_up_pixel_buffer_dma_dev* pixel_buffer;
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");
	if (pixel_buffer == 0) {
		printf("error initializing pixel buffer (check name in alt_up_pixel_buffer_dma_open_dev)\n");
	}
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer, PIXEL_BUFFER_BASE);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

	int hw = 0;
	if (hw) {
           IOWR_32DIRECT(drawer_base,0,10); // Set x1
           IOWR_32DIRECT(drawer_base,4,20); // Set y1
           IOWR_32DIRECT(drawer_base,8,50); // Set x2
           IOWR_32DIRECT(drawer_base,12,60); // Set y2
           IOWR_32DIRECT(drawer_base,16,0xFFFF);  // Set colour
           IOWR_32DIRECT(drawer_base,20,1);  // Start drawing
           while(IORD_32DIRECT(drawer_base,20)==0); // wait until done
 	} else {
           alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 10,20,50,60,0xFFFF,0);
 	}
    return 0;
}
