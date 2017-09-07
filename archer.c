//
// Created by pierre on 24/08/17.
//

#include "global.h"
#include "archer.h"
#include "arrow.h"
#include "window_conf_reader.h"
#include "brigade_reader.h"
#include "counted_allocations.h"
void set_archer_class(entity* ent){
    entity_behaviour* c = counted_malloc(sizeof(entity_behaviour), "create behaviour for archer");
    set_basic_behaviour(c);
    c->type = ARCHER;
    c->get_current_range = archer_get_current_range;
    c->get_dying_animation = archer_get_dying_animation;
    c->get_walking_animation = archer_get_walking_animation;
    c->to_attack = archer_to_attack;
    c->attacking = archer_attacking;
    int * curr_state = counted_malloc(sizeof(int), "create state for archer");
    *curr_state = KICKER_NONE;
    c->current_state = curr_state;
    ent->type = c;
    ent->drawable = drawable_entity_init(animation_frame_init(get_animations()->archer_walk),
                                         &ent->pos, &ent->facing, ent->brigade->base_size);
}


animation* archer_get_dying_animation(__attribute__ ((unused))entity* ent){
    return get_animations()->archer_death;
}

animation* archer_get_walking_animation(__attribute__ ((unused))entity* ent){
    return get_animations()->archer_walk;
}


void archer_attacking(entity* ent, battle* g){
    int* current_state = ent->type->current_state;
    archer_stats* stats = ent->brigade->specific_stats;
    if (!(ent->state == ENTITY_STATE_ATTACK_FAILING) && drawable_entity_get_frame(ent->drawable) == 12){
        switch (*current_state){
            case ARCHER_SHORT_HIT:
                ent->target->type->take_damage(ent->target,((archer_stats*)(ent->brigade->specific_stats))->short_range_damage);
                break;
            case ARCHER_CRIT:
                battle_add_projectile(g,arrow_create((int)ent->pos,(unsigned int)stats->range, (unsigned int)stats->arrow_speed,stats->arrow_size, ent->team, ent->facing, stats->critical_damage));
            case ARCHER_NORMAL:
                battle_add_projectile(g,arrow_create((int)ent->pos,(unsigned int)stats->range, (unsigned int)stats->arrow_speed,stats->arrow_size, ent->team, ent->facing, stats->normal_damage));
        }
    }
    drawable_entity_animation_forward(ent->drawable, (float)stats->basic_attack_speed/(float)get_window_config()->fps);
}

__attribute__ ((pure)) int archer_get_current_range(entity* ent){
    archer_stats* k = (archer_stats*)(ent->brigade->specific_stats);
    return k->range;
}

void archer_to_attack(entity* ent,entity* target){
    archer_stats* stats = ent->brigade->specific_stats;
    int* current_state = ent->type->current_state;
    ent->state = ENTITY_STATE_ATTACKING;
    animation_frame_destroy(ent->drawable->anim);
    if (ent->pos > target->pos){
        ent->facing = 1;
    }
    ent->target = target;
    if (abs(ent->pos  - target->pos)<stats->range_short){
        *current_state = ARCHER_SHORT_HIT;
        ent->drawable->anim = animation_frame_init(get_animations()->archer_short_hit);
    } else {
        if ((rand() % stats->critical_chance)) {
            *current_state = ARCHER_NORMAL;
            ent->drawable->anim = animation_frame_init(get_animations()->archer_hit);
        } else {
            *current_state = ARCHER_CRIT;
            ent->drawable->anim = animation_frame_init(get_animations()->archer_critical_hit);
        }
    }
}
