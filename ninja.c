//
// Created by pierre on 22/08/17.
//

#include "ninja.h"
#include "global.h"
#include "window_conf_reader.h"
ninja* ninja_init(int level){
    ninja* k = malloc(sizeof(ninja));
    k->range = NINJA_RANGE;
    k->attack_type = NINJA_NONE;
    k->will_jump = rand()%2;
    return k;
}

void set_ninja_class(entity* ent, int level){
    entity_behaviour* c = malloc(sizeof(entity_behaviour));
    set_basic_behaviour(c);
    c->type = NINJA;
    c->get_current_range = ninja_get_current_range;
    c->get_dying_animation = ninja_get_dying_animation;
    c->get_walking_animation = ninja_get_walking_animation;
    c->to_attack = ninja_to_attack;
    c->attacking = ninja_attacking;
    c->type_stats = ninja_init(level);
    ent->type = c;
}

animation* ninja_get_dying_animation(entity* ent){
    return get_animations()->ninja_death;
}
animation* ninja_get_walking_animation(entity* ent){
    return get_animations()->ninja_walk;
}


void ninja_attacking(entity* ent, game* g) {
    int curr_frame = drawable_entity_get_frame(ent->drawable);
    switch (((ninja *) ent->type->type_stats)->attack_type) {
        case HIT :
            if (curr_frame == 12) {
                if (ent->state != ENTITY_STATE_ATTACK_FAILING){
                    ent->target->hp -= NINJA_HIT_DAMAGE;
                }
                ((ninja *) ent->type->type_stats)->will_jump = rand() % 2;
            }
            break;
        case SLASH :
            if (curr_frame == 12) {
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
    drawable_entity_animation_forward(ent->drawable, NINJA_BASE_ATTACK_SPEED/get_window_config()->fps);
}

void ninja_jumping(entity* ent){
    int curr_frame = drawable_entity_get_frame(ent->drawable);
    if (curr_frame > 22 && curr_frame < 33) {
        float moving_by = ent->speed  * 3;
        if (ent->state != ENTITY_STATE_ATTACK_FAILING) {
            int nb_frame_remaining = 33 - curr_frame;
            moving_by = abs(ent->pos-ent->target->pos)/nb_frame_remaining;
        }
        ent->pos -= moving_by * (2 * ent->facing - 1);
    }
    if (drawable_entity_get_frame(ent->drawable) == 33) {
        if (ent->state != ENTITY_STATE_ATTACK_FAILING) {
            ent->target->hp -= NINJA_SLASH_DAMAGE;
        }
        ((ninja *) ent->type->type_stats)->will_jump = rand() % 2;
    }
    drawable_entity_animation_forward(ent->drawable, NINJA_BASE_ATTACK_SPEED/get_window_config()->fps);
}

int ninja_get_current_range(entity* ent){
    ninja* k = (ninja*)(ent->type->type_stats);
    return k->will_jump?NINJA_RANGE:NINJA_JUMP_RANGE;
}

void ninja_to_attack(entity* ent,entity* target){
    ent->state = ENTITY_STATE_ATTACKING;
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
