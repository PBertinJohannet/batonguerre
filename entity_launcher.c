//
// Created by pierre on 23/08/17.
//
#include "entity_launcher.h"
#include "global.h"
#include "counted_allocations.h"
#include "window_conf_reader.h"
entity_launcher* entity_launcher_init(brigade* brigade1, int cost, int cd){
    entity_launcher* ent = counted_malloc(sizeof(entity_launcher), "entity launcher create");
    ent->cost = cost;
    ent->cd = cd;
    ent->brigade = brigade1;
    ent->curr_cd = ent->cd;
    return ent;
}
void entity_launcher_set_type(entity_launcher* ent, int type){
    switch (type){
        case KICKER:
            ent->anim = animation_frame_init(get_animations()->kicker_icon);
            break;
        case NINJA:
            ent->anim = animation_frame_init(get_animations()->ninja_icon);
            break;
        case ARCHER:
            ent->anim = animation_frame_init(get_animations()->kicker_icon);
            break;
        case MINEWORKER:
            ent->anim = animation_frame_init(get_animations()->kicker_icon);
            break;
    }
}
void entity_launcher_update(entity_launcher* ent){
    if (ent->curr_cd < ent->cd) {
        ent->curr_cd +=1.0*get_elapsed_sec();
    }
}


sfSprite* entity_launcher_get_icon(entity_launcher* ent){
    sfSprite* sprite = sfSprite_counted_malloc("creating sprite for entity launcher");
    sfSprite_setTexture(sprite, ent->anim->anim->texture, sfTrue);
    int frame = (int)((ent->curr_cd/(float)ent->cd)
                      * (float)ent->anim->anim->nb_frames) -1 ;
    sfIntRect target = ent->anim->anim->frames[frame];
    sfSprite_setTextureRect(sprite, target);
    return sprite;
}
__attribute_pure__ int can_launch(entity_launcher* ent){
    return ((int)ent->curr_cd) == ent->cd && ent->brigade->team->gold > ent->cost;
}

void entity_launcher_launch(entity_launcher* launcher, battle* g){
    if (can_launch(launcher)) {
        launcher->curr_cd = 0;
        launcher->brigade->team->gold-=launcher->cost;
        battle_add_entity(g, factory_new_entity(launcher->brigade));
    } else {
        // refused
    }
}

void entity_launcher_destroy(void* ent){
    animation_frame_destroy(((entity_launcher*)ent)->anim);
    counted_free(ent, "freeing entity launcher");
}