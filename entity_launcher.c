//
// Created by pierre on 23/08/17.
//
#include "entity_launcher.h"

entity_launcher* entity_launcher_init(int ent_type, int level,int cost, int cd, animation* anim, int team){
    entity_launcher* ent = malloc(sizeof(entity_launcher));
    ent->ent_type = ent_type;
    ent->level = level;
    ent->cost = cost;
    ent->cd = cd;
    ent->team = team;
    ent->anim = animation_frame_init(anim);
    ent->curr_cd = ent->cd;
    return ent;
}
void entity_launcher_update(entity_launcher* ent){
    if (ent->curr_cd < ent->cd) {
        ent->curr_cd ++;
    }
}


sfSprite* entity_launcher_get_icon(entity_launcher* ent){
    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, ent->anim->anim->texture, sfTrue);
    int frame = (int)(((float)ent->curr_cd/(float)ent->cd) * (float)ent->anim->anim->nb_frames)-1;
    sfIntRect target = ent->anim->anim->frames[frame];
    sfSprite_setTextureRect(sprite, target);
    return sprite;
}

void entity_launcher_launch(entity_launcher* launcher, game* g){
    if (launcher->curr_cd == launcher->cd && game_get_team(g,launcher->team)->gold > launcher->cost) {
        launcher->curr_cd = 0;
        game_get_team(g,launcher->team)->gold-=launcher->cost;
        game_add_entity(g, factory_new_entity(launcher->ent_type, launcher->team, launcher->level, g));
    } else {
        // refused
    }
}

int entity_launcher_destroy(void* ent){
    animation_frame_destroy(((entity_launcher*)(ent))->anim);
    free(ent);
    return 0;
}