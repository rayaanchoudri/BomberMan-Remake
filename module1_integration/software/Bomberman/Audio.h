/*
 * Audio.h
 *
 *  Created on: 2014-10-14
 *      Author: Lucas
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include "Altera_UP_SD_Card_Avalon_Interface.h"
#include "altera_up_avalon_audio_and_video_config.h"
#include "altera_up_avalon_audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/alt_irq.h>

#define BUF_SIZE 96

class Audio{
	public:

	void load_audio();
	unsigned long rand();

};


#endif /* AUDIO_H_ */
