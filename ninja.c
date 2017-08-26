//
// Created by pierre on 22/08/17.
//

#include "ninja.h"
#include "global.h"
ninja* ninja_init(int level){
    ninja* k = malloc(sizeof(ninja));
    k->range = NINJA_RANGE;
    k->attack_type = NINJA_NONE;
    k->will_jump = rand()%2;
    return k;
}

void set_ninja_class(entity* ent, int level){
    entity_type* c = malloc(sizeof(entity_type));
    c->type = NINJA;
    c->type_stats = ninja_init(level);
    c->play = entity_base_play;
    c->get_current_range = ninja_get_current_range;
    c->to_attack = ninja_to_attack;
    c->to_aggro = ninja_to_aggro;
    c->attack = ninja_attack;
    c->to_dying = ninja_to_dying;
    c->retreating = ninja_retreating;
    ent->type = c;
}


void ninja_retreating(entity* ent, list* entities){
    if (ent->drawable->anim->anim != get_animations()->ninja_walk){
        animation_frame_destroy(ent->drawable->anim);
        ent->drawable->anim = animation_frame_init(get_animations()->ninja_walk);
    }
    //int team_coeff = 1000*ent->team + (2*ent->team+1)*RETREAT_PLAYER;
    if ((int)(abs(ent->pos-ent->team*MAP_SIZE))>RETREAT_PLAYER){
        ent->facing = !ent->team;
        ent->pos -= ent->speed * (2 * ent->facing - 1);
    } else {
        entity_base_find_target(ent, entities);
    }
}

void ninja_to_dying(entity* ent){
    ent->state = ENTITY_STATE_DYING;
    ent->drawable->anim = animation_frame_init(get_animations()->ninja_death);
}

void ninja_attack(entity* ent, game* g) {
    switch (((ninja *) ent->type->type_stats)->attack_type) {
        case HIT :
            if (ent->drawable->anim->frame == 12) {
                if (ent->state != ENTITY_STATE_ATTACK_FAILING){
                    ent->target->hp -= NINJA_HIT_DAMAGE;
                }
                ((ninja *) ent->type->type_stats)->will_jump = rand() % 2;
            }
            break;
        case SLASH :
            if (ent->drawable->anim->frame == 12) {
                if (ent->state != ENTITY_STATE_ATTACK_FAILING) {
                    ent->target->hp -= NINJA_SLASH_DAMAGE;
                }
                ((ninja *) ent->type->type_stats)->will_jump = rand() % 2;
            }
            break;
        case NINJA_JUMP :
            ninja_jumping(ent);
        default:
            break;
    }
}

void ninja_jumping(entity* ent){
    if (ent->drawable->anim->frame > 22 && ent->drawable->anim->frame < 33) {
        float moving_by = ent->speed  * 3;
        if (ent->state != ENTITY_STATE_ATTACK_FAILING) {
            int nb_frame_remaining = 33 - ent->drawable->anim->frame;
            moving_by = abs(ent->pos-ent->target->pos)/nb_frame_remaining;
        }
        ent->pos -= moving_by * (2 * ent->facing - 1);
    }
    if (ent->drawable->anim->frame == 33) {
        if (ent->state != ENTITY_STATE_ATTACK_FAILING) {
            ent->target->hp -= NINJA_SLASH_DAMAGE;
        }
        ((ninja *) ent->type->type_stats)->will_jump = rand() % 2;
    }
}

int ninja_get_current_range(entity* ent){
    ninja* k = (ninja*)(ent->type->type_stats);
    return k->will_jump?NINJA_RANGE:NINJA_JUMP_RANGE;
}

void ninja_to_attack(entity* ent,entity* target){
    if (abs(ent->pos-target->pos)>NINJA_RANGE){
        ninja_to_jump_attack(ent, target);
    } else {
        ninja_to_short_attack(ent, target);
    }
}

void ninja_to_short_attack(entity* ent, entity* target){
    ent->state = ENTITY_STATE_ATTACKING;
    animation_frame_destroy(ent->drawable->anim);
    ent->target = target;
    if (rand()%NINJA_HIT_CHANCE) {
        ((ninja *) (ent->type->type_stats))->attack_type = HIT;
        ent->drawable->anim = animation_frame_init(get_animations()->ninja_strike);
    } else {
        ((ninja *) (ent->type->type_stats))->attack_type = SLASH;
        ent->drawable->anim = animation_frame_init(get_animations()->ninja_slash);
    }
}
void ninja_to_jump_attack(entity* ent, entity* target){
    ent->state = ENTITY_STATE_ATTACKING;
    animation_frame_destroy(ent->drawable->anim);
    ent->target = target;
    ((ninja *) (ent->type->type_stats))->attack_type = NINJA_JUMP;
    ent->drawable->anim = animation_frame_init(get_animations()->ninja_jump);
}

void ninja_to_aggro(entity* ent) {
    ent->state = ENTITY_STATE_ASSAULT;
    animation_frame_destroy(ent->drawable->anim);
    ent->drawable->anim = animation_frame_init(get_animations()->ninja_walk);
}