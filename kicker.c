//
// Created by pierre on 22/08/17.
//
#include "kicker.h"
#include "time.h"
#include "global.h"
#include "window_conf_reader.h"
#include "brigade_reader.h"
#include "counted_allocations.h"
void set_kicker_class(entity* ent){
    entity_behaviour* c = counted_malloc(sizeof(entity_behaviour), "create kicker behaviour");
    set_basic_behaviour(c);
    c->type =KICKER;
    c->get_current_range = kicker_get_current_range;
    c->get_dying_animation = kicker_get_dying_animation;
    c->get_walking_animation = kicker_get_walking_animation;
    c->to_attack = kicker_to_attack;
    c->attacking = kicker_attacking;
    int * curr_state = counted_malloc(sizeof(int), "create kicker state");
    *curr_state = KICKER_NONE;
    c->current_state = curr_state;
    ent->type = c;
    ent->drawable = drawable_entity_init(animation_frame_init(get_animations()->stick_walk),
                                         &ent->pos, &ent->facing, ent->brigade->base_size);
}

animation* kicker_get_dying_animation(entity* ent){
    if (ent->state == ENTITY_STATE_ASSAULT
        || ent->drawable->anim->frame < 6
        || ent->drawable->anim->frame > 16){
        return get_animations()->stick_walk_death;
    }
    return get_animations()->stick_kick_death;
}

animation* kicker_get_walking_animation(__attribute__ ((unused))entity* ent){
    return get_animations()->stick_walk;
}


void kicker_attacking(entity* ent,__attribute__ ((unused)) battle* g){
    int* current_state = ent->type->current_state;
    kicker_stats* stats = ent->brigade->specific_stats;
    float base_attack_speed = ( *current_state == PUNCH)?stats->punch_attack_speed:stats->base_attack_speed;
    if (!(ent->state == ENTITY_STATE_ATTACK_FAILING) && drawable_entity_get_frame(ent->drawable) == 11){
        int damage = stats->punch_damage;
        if (*current_state == PUNCH){
            damage = stats->kick_damage;
        }
        ent->target->type->take_damage(ent->target, damage);
        ent->state = ENTITY_STATE_ATTACK_FAILING;
    }
    drawable_entity_animation_forward(ent->drawable, base_attack_speed*get_elapsed_sec());
}

__attribute__ ((pure))int kicker_get_current_range(entity* ent){
    kicker_stats* k = (kicker_stats*)(ent->brigade->specific_stats);
    return k->range;
}

void kicker_to_attack(entity* ent,entity* target){
    if (ent->pos > target->pos){
        ent->facing = 1;
    }
    kicker_stats* stats = ent->brigade->specific_stats;
    int* current_state = ent->type->current_state;
    ent->state = ENTITY_STATE_ATTACKING;
    animation_frame_destroy(ent->drawable->anim);
    ent->target = target;
    if (rand()%stats->punch_chance) {
        *current_state = PUNCH;
        ent->drawable->anim = animation_frame_init( get_animations()->kicker_punch);
    } else {
        *current_state = KICK;
        ent->drawable->anim = animation_frame_init( get_animations()->stick_kick);
    }
}
