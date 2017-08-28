//
// Created by pierre on 22/08/17.
//

#include "base.h"
#include "global.h"
base* base_init(int level){
    base* k = malloc(sizeof(base));
    k->range = 0;
    k->damage = 0;
    return k;
}

void set_base_class(entity* ent, int level){
    entity_behaviour* c = malloc(sizeof(entity_behaviour));
    set_basic_behaviour(c);
    c->type =BASE;
    c->get_current_range = base_get_current_range;
    c->get_dying_animation = base_get_dying_animation;
    c->get_walking_animation = base_get_walking_animation;
    c->play = base_play;
    c->to_attack = base_to_attack;
    c->attacking = base_attacking;
    c->type_stats = base_init(level);
    ent->type = c;
}


animation* base_get_dying_animation(entity* ent){
    return get_animations()->stick_walk_death;
}

animation* base_get_walking_animation(entity* ent){
    return get_animations()->stick_walk;
}


void base_play(game* g, entity* player, list* entities){
    player->drawable->anim->frame =player->drawable->anim->anim->nb_frames-3;
}

void base_attacking(entity* ent, game* g){
    ent->drawable->anim->frame = 0;
}

int base_get_current_range(entity* ent){
    return 0;
}

void base_to_attack(entity* ent,entity* target){

}
