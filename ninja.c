//
// Created by pierre on 22/08/17.
//

#include "ninja.h"
#include "global.h"
#include "window_conf_reader.h"
#include "brigade_reader.h"
#include "counted_allocations.h"
#include "time.h"
ninja* ninja_init(ninja_stats* stats){
    ninja* k = counted_malloc(sizeof(ninja), "create ninja stats");
    k->attack_type = NINJA_NONE;
    k->will_jump = rand()%100 > stats->jump_chance;
    return k;
}

void set_ninja_class(entity* ent){
    entity_behaviour* c = counted_malloc(sizeof(entity_behaviour), "create ninja behaviour");
    set_basic_behaviour(c);
    c->type = NINJA;
    c->get_current_range = ninja_get_current_range;
    c->get_dying_animation = ninja_get_dying_animation;
    c->get_walking_animation = ninja_get_walking_animation;
    c->to_attack = ninja_to_attack;
    c->attacking = ninja_attacking;
    ninja * curr_state = ninja_init((ninja_stats*)ent->brigade->specific_stats);
    c->current_state = curr_state;
    ent->type = c;
    ent->drawable = drawable_entity_init(animation_frame_init(get_animations()->ninja_walk),
                                         &ent->pos, &ent->facing, ent->brigade->base_size);
}

animation* ninja_get_dying_animation( entity* ent){
    return get_animations()->ninja_death;
}
animation* ninja_get_walking_animation( entity* ent){
    return get_animations()->ninja_walk;
}


void ninja_attacking(entity* ent,  battle* g) {
    ninja* current_state = ent->type->current_state;
    ninja_stats* stats = ent->brigade->specific_stats;
    unsigned int curr_frame = drawable_entity_get_frame(ent->drawable);
    switch (current_state->attack_type) {
        case HIT :
            if (curr_frame == 12) {
                if (ent->state != ENTITY_STATE_ATTACK_FAILING){
                    ent->target->type->take_damage(ent->target, stats->hit_damage);
                    ent->state = ENTITY_STATE_ATTACK_FAILING;
                }
                current_state->will_jump = rand() % 2;
            }
            break;
        case SLASH :
            if (curr_frame == 12) {
                if (ent->state != ENTITY_STATE_ATTACK_FAILING) {
                    ent->target->type->take_damage(ent->target, stats->slash_damage);
                    ent->state = ENTITY_STATE_ATTACK_FAILING;
                }
                current_state->will_jump = rand() % 2;
            }
            break;
        case NINJA_JUMP :
            ninja_jumping(ent);
        default:
            break;
    }
    drawable_entity_animation_forward(ent->drawable, stats->basic_attack_speed*get_elapsed_sec());
}

void ninja_jumping(entity* ent){
    ninja_stats* stats = ent->brigade->specific_stats;
    unsigned int curr_frame = drawable_entity_get_frame(ent->drawable);
    if (curr_frame > 22 && curr_frame < 33) {
        float moving_by = ent->speed *get_elapsed_sec() * 3;
        if (ent->state != ENTITY_STATE_ATTACK_FAILING) {
            unsigned int nb_frame_remaining = 33 - curr_frame;
            moving_by = abs(ent->pos-ent->target->pos)/(float)nb_frame_remaining;
        }
        ent->pos -= moving_by * (2 * ent->facing - 1);
    }
    if (drawable_entity_get_frame(ent->drawable) == 33) {
        if (ent->state != ENTITY_STATE_ATTACK_FAILING) {
            ent->target->type->take_damage(ent->target, stats->jump_damage);
            ent->state = ENTITY_STATE_ATTACK_FAILING;
        }
        ((ninja *) ent->type->current_state)->will_jump = rand() % 2;
    }
    drawable_entity_animation_forward(ent->drawable, stats->basic_attack_speed*get_elapsed_sec());
}

int ninja_get_current_range(entity* ent){
    ninja_stats* stats = ent->brigade->specific_stats;
    ninja* k = (ninja*)(ent->type->current_state);
    return k->will_jump?stats->range:stats->jump_range;
}

void ninja_to_attack(entity* ent,entity* target){
    if (ent->pos > target->pos){
        ent->facing = 1;
    }
    ninja_stats* stats = ent->brigade->specific_stats;
    ent->state = ENTITY_STATE_ATTACKING;
    if (abs(ent->pos-target->pos)>stats->range){
        ninja_to_jump_attack(ent, target);
    } else {
        ninja_to_short_attack(ent, target);
    }
}

void ninja_to_short_attack(entity* ent, entity* target){
    ninja_stats* stats = ent->brigade->specific_stats;
    ent->state = ENTITY_STATE_ATTACKING;
    animation_frame_destroy(ent->drawable->anim);
    ent->target = target;
    if (rand()%stats->hit_chance) {
        ((ninja *) (ent->type->current_state))->attack_type = HIT;
        ent->drawable->anim = animation_frame_init(get_animations()->ninja_strike);
    } else {
        ((ninja *) (ent->type->current_state))->attack_type = SLASH;
        ent->drawable->anim = animation_frame_init(get_animations()->ninja_slash);
    }
}
void ninja_to_jump_attack(entity* ent, entity* target){
    ent->state = ENTITY_STATE_ATTACKING;
    animation_frame_destroy(ent->drawable->anim);
    ent->target = target;
    ((ninja *) (ent->type->current_state))->attack_type = NINJA_JUMP;
    ent->drawable->anim = animation_frame_init(get_animations()->ninja_jump);
}
