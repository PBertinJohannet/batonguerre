
#include <SFML/Graphics.h>
#include "game_state.h"

int main()
{
    game_state * state = playing_state_init();
    game_state_loop(state);
    return 0;
}
