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


void archer_attacking(entity* ent, game* g){
    int* current_state = ent->type->current_state;
    if (!(ent->state == ENTITY_STATE_ATTACK_FAILING) && drawable_entity_get_frame(ent->drawable) == 12){
        switch (*current_state){
            case ARCHER_SHORT_HIT:
                ent->target->hp-=((archer_stats*)(ent->brigade->specific_stats))->short_range_damage;
                break;
            case ARCHER_CRIT:
                game_add_projectile(g,arrow_create(ent->pos, ent->team, ent->facing, ARCHER_CRIT_DAMAGE));
            case ARCHER_NORMAL:
                game_add_projectile(g,arrow_create(ent->pos, ent->team, ent->facing, ARCHER_NORMAL_DAMAGE));
        }
    }
    drawable_entity_animation_forward(ent->drawable, ARCHER_BASE_ATTACK_SPEED/get_window_config()->fps);
}

__attribute__ ((pure)) int archer_get_current_range(entity* ent){
    archer_stats* k = (archer_stats*)(ent->brigade->specific_stats);
    return k->range;
}

void archer_to_attack(entity* ent,entity* target){
    int* current_state = ent->type->current_state;
    ent->state = ENTITY_STATE_ATTACKING;
    animation_frame_destroy(ent->drawable->anim);
    ent->target = target;
    if (abs(ent->pos  - target->pos)<ARCHER_SHORT_RANGE){
        *current_state = ARCHER_SHORT_HIT;
        ent->drawable->anim = animation_frame_init(get_animations()->archer_short_hit);
    } else {
        if ((rand() % ARCHER_CRIT_CHANCE)) {
            *current_state = ARCHER_NORMAL;
            ent->drawable->anim = animation_frame_init(get_animations()->archer_hit);
        } else {
            *current_state = ARCHER_CRIT;
            ent->drawable->anim = animation_frame_init(get_animations()->archer_critical_hit);
        }
    }
}
