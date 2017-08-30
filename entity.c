//
// Created by pierre on 21/08/17.
//
#include "entity.h"
#include "window_conf_reader.h"
entity* entity_init(int hp, float speed, team* team, float size, float pos,  animation_frame* frame){
    entity* ent = malloc(sizeof(entity));
    ent->pos = pos;
    ent->hp = hp;
    ent->speed = speed / (float)get_window_config()->fps;
    ent->team = team;
    ent->facing = team->id;
    ent->drawable = drawable_entity_init(frame,&ent->pos,&ent->facing,size);
    return ent;
}

void set_entity_type(entity* ent, struct entity_behaviour* type){
    ent->type = type;
}

void entity_destroy(entity* ent){
    drawable_entity_destroy(ent->drawable);
    entity_behaviour_destroy(ent->type);
    free(ent);
}


command* entity_get_command(entity* ent){
    return entity_get_brigade(ent)->command;
}
brigade* entity_get_brigade(entity* ent){
    return ((brigade*)list_at(ent->team->brigades,ent->type->type));
}

int entity_destroy_void(void* ent){
    entity_destroy(ent);
    return 0;
}