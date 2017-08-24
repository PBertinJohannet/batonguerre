//
// Created by pierre on 22/08/17.
//
#include "kicker.h"
#include "time.h"
#include "global.h"
kicker* kicker_init(int level){
    kicker* k = malloc(sizeof(kicker));
    k->range = KICKER_RANGE;
    k->damage = level;
    k->attack_type = KICKER_NONE;
    return k;
}

void set_kicker_class(entity* ent, int level){
    entity_type* c = malloc(sizeof(entity_type));
    c->type_stats = kicker_init(level);
    c->play = entity_base_play;
    c->get_current_range = kicker_get_current_range;
    c->to_attack = kicker_to_attack;
    c->to_aggro = kicker_to_aggro;
    c->attack = kicker_attack;
    c->to_dying = kicker_to_dying;
    c->retreating = kicker_retreating;
    ent->type = c;
}

void kicker_retreating(entity* ent ){
    if (ent->drawable->anim->anim !=  get_animations()->stick_walk){
        animation_frame_destroy(ent->drawable->anim);
        ent->drawable->anim = animation_frame_init( get_animations()->stick_walk);
    }
    //int team_coeff = 1000*ent->team - (2*ent->team+1)*RETREAT_PLAYER;
    if ((int)(abs(ent->pos-ent->team*MAP_SIZE))>RETREAT_PLAYER){
        ent->facing = !ent->team;
        ent->pos -= ent->speed * (2 * ent->facing - 1) ;
    } else {
        ent->facing = ent->team;
    }
}


void kicker_to_dying(entity* ent ){
    ent->state = DYING;
    animation_frame* new_anim;
    if (ent->state == AGG_MOVING
        || ent->drawable->anim->frame < 6
        || ent->drawable->anim->frame > 16){
        new_anim = animation_frame_init( get_animations()->stick_walk_death);
        ent->pos += 60 * (ent->facing * 2 - 1);
    } else {
        new_anim = animation_frame_init( get_animations()->stick_kick_death);
        new_anim->frame = ent->drawable->anim->frame;
    }
    animation_frame_destroy(ent->drawable->anim);
    ent->drawable->anim = new_anim;
}

void kicker_attack(entity* ent, game* g){
    if (!(ent->state == ATTACK_FAILING) && ent->drawable->anim->frame == 11){
        int damage = KICKER_KICK_DAMAGE;
        if (((kicker*)ent->type->type_stats)->attack_type == PUNCH){
            damage = KICKER_PUNCH_DAMAGE;
        }
        ent->target->hp-=((kicker*)ent->type->type_stats)->damage + damage;

    }
}

int kicker_get_current_range(entity* ent){
    kicker* k = (kicker*)(ent->type->type_stats);
    return k->range;
}

void kicker_to_attack(entity* ent,entity* target){
    ent->state = ATTACKING;
    animation_frame_destroy(ent->drawable->anim);
    ent->target = target;
    if (rand()%KICKER_PUNCH_CHANCE) {
        ((kicker *) (ent->type->type_stats))->attack_type = PUNCH;
        ent->drawable->anim = animation_frame_init( get_animations()->kicker_punch);
    } else {
        ((kicker *) (ent->type->type_stats))->attack_type = KICK;
        ent->drawable->anim = animation_frame_init( get_animations()->stick_kick);
    }
}

void kicker_to_aggro(entity* ent){
    ent->state = AGG_MOVING;
    animation_frame_destroy(ent->drawable->anim);
    ent->drawable->anim = animation_frame_init( get_animations()->stick_walk);
}