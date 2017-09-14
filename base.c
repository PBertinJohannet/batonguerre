//
// Created by pierre on 22/08/17.
//

#include "base.h"
#include "window_conf_reader.h"
#include "global.h"
#include "counted_allocations.h"
entity* base_init(int pos, int hp, team* team){
    entity* ent = counted_malloc(sizeof(entity), "create base init");
    ent->pos = pos;
    ent->hp = hp;
    ent->speed = 0;
    ent->team = team;
    ent->facing = ent->team->id;
    ent->drawable = drawable_entity_init(animation_frame_init(get_animations()->stick_walk), &ent->pos, &ent->facing, 4);
    ent->state = ENTITY_STATE_ATTACKING;
    return ent;
}
void set_base_class(entity* ent){
    entity_behaviour* c = counted_malloc(sizeof(entity_behaviour), "create base behaviour");
    set_basic_behaviour(c);
    c->type =BASE;
    c->get_current_range = base_get_current_range;
    c->get_dying_animation = base_get_dying_animation;
    c->get_walking_animation = base_get_walking_animation;
    c->play = base_play;
    c->to_attack = base_to_attack;
    c->attacking = base_attacking;
    c->current_state = counted_malloc(0, "allocated current state for base");
    c->take_damage = base_take_damage;
    ent->type = c;
}

void base_take_damage(entity* ent, int damages){
    if (2<damages){
        ent->hp-=(damages - 2);
    }
}



animation* base_get_dying_animation(__attribute__ ((unused))entity* ent){
    return get_animations()->stick_walk_death;
}

animation* base_get_walking_animation(__attribute__ ((unused))entity* ent){
    return get_animations()->stick_walk;
}


void base_play(__attribute__ ((unused))battle* g, entity* player,__attribute__ ((unused)) list* entities){
    player->drawable->anim->frame =player->drawable->anim->anim->nb_frames-3;
}

void base_attacking(entity* ent,__attribute__ ((unused)) battle* g){
    ent->drawable->anim->frame = 0;
}

__attribute__ ((const)) int base_get_current_range(__attribute__ ((unused))entity* ent){
    return 0;
}

__attribute__ ((const)) void base_to_attack(__attribute__ ((unused))entity* ent,__attribute__ ((unused))entity* target){

}
