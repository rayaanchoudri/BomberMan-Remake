/*
 * Audio.cpp
 *
 *  Created on: 2014-10-14
 *      Author: Lucas
 */

#include "Audio.h"

alt_up_audio_dev * audio;
volatile long current_audio_stream_pos;
unsigned int *mono_audio_stream;
long stream_size;
volatile unsigned long rand_cicles = 0;

void av_config_setup() {
	printf("\n****************************\n\n");
	printf("Configuring audio...\n");
	alt_up_av_config_dev * av_config = alt_up_av_config_open_dev(
			"/dev/audio_and_video_config_0");
	while (!alt_up_av_config_read_ready(av_config)) {
	}
	printf(" done!\n");
}

void audio_isr(void * context, alt_u32 irq_id) {
	alt_up_audio_write_fifo(audio, &mono_audio_stream[current_audio_stream_pos],
			BUF_SIZE, ALT_UP_AUDIO_LEFT);
	alt_up_audio_write_fifo(audio, &mono_audio_stream[current_audio_stream_pos],
			BUF_SIZE, ALT_UP_AUDIO_RIGHT);
	current_audio_stream_pos += BUF_SIZE;
	if (current_audio_stream_pos >= stream_size - BUF_SIZE) {
		current_audio_stream_pos = 0;
	}
	rand_cicles++;
}

void Audio::load_audio() {
	av_config_setup();

	current_audio_stream_pos = 0;
	mono_audio_stream = NULL;
	stream_size = 0;

	alt_up_sd_card_dev *sd_card = NULL;
	int connected = 0;
	short int music_file;
	long file_size;

	audio = alt_up_audio_open_dev("/dev/audio_0");
	if (audio == NULL) {
		printf("--- Failed to open audio device!\n");
		exit(0);
	}
	alt_up_audio_reset_audio_core(audio);

	sd_card = alt_up_sd_card_open_dev(
			"/dev/Altera_UP_SD_Card_Avalon_Interface_0");
	if (sd_card == NULL) {
		printf("--- Failed to open SD card device!\n");
		exit(0);
	}

	printf("Remember to insert SD card!\n");
	while (1) {
		if ((connected == 0) && (alt_up_sd_card_is_Present())) {
			printf("Card connected.\n");
			if (alt_up_sd_card_is_FAT16()) {
				printf("FAT16 file system detected.\n");
				break;
			} else {
				printf("--- Unknown file system.\n");
			}
			connected = 1;
		} else if ((connected == 1) && (alt_up_sd_card_is_Present() == false)) {
			printf("Card disconnected.\n");
			connected = 0;
		}
	}

	music_file = alt_up_sd_card_fopen("m3.wav", false);
	if (music_file == -1) {
		printf("--- Could not open file!\n");
		exit(0);
	}

	printf("Reading file header...\n");
	char a;
	char b;
	char *data_str = "data";
	int j = 0;
	for (int i = 0; i < 45; i++) {
		a = (char) alt_up_sd_card_read(music_file);
		//printf("%c", a);
		if (a == data_str[j]) {
			j++;
			if (j == 3) {
				printf("file size found!\n");
				alt_up_sd_card_read(music_file); // letter A
				char byte_0 = (char) alt_up_sd_card_read(music_file);
				char byte_1 = (char) alt_up_sd_card_read(music_file);
				char byte_2 = (char) alt_up_sd_card_read(music_file);
				char byte_3 = (char) alt_up_sd_card_read(music_file);
				file_size = ((unsigned char) byte_3 << 24)
						| ((unsigned char) byte_2 << 16)
						| ((unsigned char) byte_1 << 8)
						| (unsigned char) byte_0;
				printf("Music file size: %lu\n", file_size);
			}
		} else {
			j = 0;
		}
	}

	printf("Allocating memory space...\n");
	mono_audio_stream = new unsigned int[file_size];
	if (mono_audio_stream == NULL) {
		printf("--- Failed to allocate left audio stream!");
		exit(1);
	}

	printf("Reading music file...\n");
	short converter;
	while (stream_size < file_size / 2) {
		b = (char) alt_up_sd_card_read(music_file);
		a = (char) alt_up_sd_card_read(music_file);
		converter = ((unsigned char) a << 8) | (unsigned char) b;
		mono_audio_stream[stream_size] = converter;

		stream_size++;
	}

	printf("done! Starting music... \n");

	printf("size: %lu, byte: 0x%08x\n", stream_size,
			mono_audio_stream[stream_size - 41]);

	alt_irq_register(AUDIO_0_IRQ, NULL, audio_isr);
	alt_irq_enable(AUDIO_0_IRQ);
	alt_up_audio_enable_write_interrupt(audio);
}

unsigned long Audio::rand(){
	return rand_cicles;
}
