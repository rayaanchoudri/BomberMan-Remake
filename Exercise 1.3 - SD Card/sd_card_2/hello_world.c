#include <stdio.h>
#include <altera_up_sd_card_avalon_interface.h>

void look_for_other_files(char *filename){
	int status = alt_up_sd_card_find_next(filename);
	while(status == 0){
		printf("%s\n", filename);
		status = alt_up_sd_card_find_next(filename);
	}

	switch (status){
		case 1: //invalid directory
			printf("Invalid Directory.\n");
			break;
		case 2: //no card present or no FAT 16 partition
			printf("Card not present or no FAT 16 partition.\n");
			break;
		case 3: //Function alt_up_sd_card_find_first should be called first
			printf("Function alt_up_sd_card_find_first should be called first.\n");
			break;
		case -1: //No files were found in the directory
			printf("No (more) files were found.\n");
			break;
	}
}

void scan_sd_card(char *directory, char *filename){
	switch (alt_up_sd_card_find_first(directory, filename)){
		case 0: //sucess
			printf("%s\n", filename);
			look_for_other_files(filename);
			break;
		case 1: //invalid directory
			printf("Invalid Directory.\n");
			break;
		case 2: //no card present or no FAT 16 partition
			printf("Card not present or no FAT 16 partition.\n");
			break;
		case -1: //No files were found in the directory
			printf("The directory is empty.\n");
			break;
	}
}


int main(void) {
	alt_up_sd_card_dev *device_reference = NULL;
	int connected = 0;
	char *filename;
	char *directory = "folder/"; // root directory

	device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0");
	printf("Program running\n");

	if (device_reference != NULL) {
		while(1) {
			if ((connected == 0) && (alt_up_sd_card_is_Present())) {
				printf("Card connected.\n");
				if (alt_up_sd_card_is_FAT16()) {
					printf("FAT16 file system detected.\n");
					scan_sd_card(directory, filename);
				} else {
					printf("Unknown file system.\n");
				}
				connected = 1;
			}
			else if ((connected == 1) && (alt_up_sd_card_is_Present() == false)) {
				printf("Card disconnected.\n");
				connected = 0;
			}
		}
	}

	printf("Device reference is wrong\n");

	return 0;
}
