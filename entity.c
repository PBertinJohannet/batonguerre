//
// Created by pierre on 21/08/17.
//
#include "entity.h"

entity* entity_init(int hp, float speed, int team, float size, float pos, int state, animation_frame* frame){
    entity* ent = malloc(sizeof(entity));
    entity_stats* stats = malloc(sizeof(entity_stats));
    stats->pos = pos;
    stats->hp = hp;
    stats->speed = speed / (float)FPS;
    stats->team = team;
    stats->facing = team;
    ent->drawable = drawable_entity_init(frame,&stats->pos,&stats->facing,size);
    stats->state = state;
    ent->stats= stats;
    return ent;
}

void set_entity_type(entity* ent, struct entity_type* type){
    ent->type = type;
}

void entity_destroy(entity* ent){
    drawable_entity_destroy(ent->drawable);
    entity_type_destroy(ent->type);
    free(ent->stats);
    free(ent);
}

int entity_destroy_void(void* ent){
    entity_destroy(ent);
    return 0;
}