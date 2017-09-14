//
// Created by pierre on 21/08/17.
//
#include "entity.h"
#include "window_conf_reader.h"
#include "counted_allocations.h"
entity* entity_init(brigade* b){
    entity* ent = counted_malloc(sizeof(entity), "entity init");
    ent->pos = b->team->pop;
    ent->hp = b->base_life;
    ent->speed = (b->base_speed + rand()%b->random_speed) / (float)get_window_config()->fps;
    ent->team = b->team;
    ent->facing = ent->team->id;
    ent->brigade = b;
    ent->state = ent->brigade->command->entity_state;
    return ent;
}

void set_entity_type(entity* ent, struct entity_behaviour* type){
    ent->type = type;
}

void entity_destroy(entity* ent){
    drawable_entity_destroy(ent->drawable);
    entity_behaviour_destroy(ent->type);
    counted_free(ent, "freeing entity ");
}


__attribute_pure__ command* entity_get_command(entity* ent){
    return entity_get_brigade(ent)->command;
}
__attribute_pure__ brigade* entity_get_brigade(entity* ent){
    return ent->brigade;
}

void entity_destroy_void(void* ent){
    entity_destroy(ent);
}