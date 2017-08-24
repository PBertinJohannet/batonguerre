//
// Created by pierre on 21/08/17.
//
#include "entity.h"

entity* entity_init(int hp, float speed, int team, float size, float pos, int state, animation_frame* frame){
    entity* ent = malloc(sizeof(entity));
    ent->pos = pos;
    ent->hp = hp;
    ent->speed = speed / (float)FPS;
    ent->team = team;
    ent->facing = team;
    ent->drawable = drawable_entity_init(frame,&ent->pos,&ent->facing,size);
    ent->state = state;
    return ent;
}

void set_entity_type(entity* ent, struct entity_type* type){
    ent->type = type;
}

void entity_destroy(entity* ent){
    drawable_entity_destroy(ent->drawable);
    entity_type_destroy(ent->type);
    free(ent);
}

int entity_destroy_void(void* ent){
    entity_destroy(ent);
    return 0;
}