#include "Game.h"

/*
 * IMPORTANT. in avalon_up_sd_card_avalon_interface.h, you may get a stupid error on the line:
 *
 ifndef bool
    typedef enum e_bool { false = 0, true = 1 } bool;
#endif
 *
 *
 *     Change ifndef bool to ifndef __cplusplus
 *
 */


int main() {
	Game game;
	game.init();
	game.run();
	return 0;
}

