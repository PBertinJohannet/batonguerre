
#include <SFML/Graphics.h>
#include "game_state.h"
#define battle
int main(void)
{
#ifdef battle
    game_state_start(menu_init());
#endif
#ifdef CONFIG
#include "battle_saver.h"
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
