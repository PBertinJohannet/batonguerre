
#include <SFML/Graphics.h>
#include "game_state.h"
#define GAME
int main()
{
#ifdef GAME
    game_state * state = playing_state_init();
    game_state_loop(state);
#endif
#ifdef CONFIG
#include "game_saver.h"
#include "global.h"
#include "array_list.h"
#include "entity_factory.h"
#include "entity.h"
    list * entities = list_create();

    animation_frame* walking = animation_frame_init(get_animations()->stick_walk);
    entity* ent = entity_init(KICKER_BASE_LIFE, KICKER_BASE_SPEED, team, KICKER_BASE_SIZE, 50.0, RETREATING, walking);
    set_kicker_class(ent,level);
#endif
    return 0;
}
