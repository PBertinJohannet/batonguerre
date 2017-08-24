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
    entity_type* c = malloc(sizeof(entity_type));
    c->type_stats = base_init(level);
    c->play = base_play;
    c->get_current_range = base_get_current_range;
    c->to_attack = base_to_attack;
    c->to_aggro = base_to_aggro;
    c->attack = base_attack;
    c->to_dying = base_to_dying;
    ent->type = c;
}


void base_to_dying(entity* ent ){
    animation_frame_destroy(ent->drawable->anim);
    ent->drawable->anim = animation_frame_init( get_animations()->stick_walk_death);
}

int base_play(game* g, entity* player, list* entities){
    player->drawable->anim->frame =player->drawable->anim->anim->nb_frames-3;
    return 0;
}

void base_attack(entity* ent, game* g){
    ent->drawable->anim->frame = 0;
}

int base_get_current_range(entity* ent){
    return 0;
}

void base_to_attack(entity* ent,entity* target){

}

void base_to_aggro(entity* ent){

}