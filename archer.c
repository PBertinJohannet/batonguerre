//
// Created by pierre on 24/08/17.
//

#include "global.h"
#include "archer.h"
#include "arrow.h"
archer* archer_init(int level){
    archer* k = malloc(sizeof(archer));
    k->range = ARCHER_LONG_RANGE;
    k->range_short = ARCHER_SHORT_RANGE;
    k->damage = level;
    k->attack_type = ARCHER_NONE;
    return k;
}

void set_archer_class(entity* ent, int level){
    entity_behaviour* c = malloc(sizeof(entity_behaviour));
    set_basic_behaviour(c);
    c->type = ARCHER;
    c->get_current_range = archer_get_current_range;
    c->get_dying_animation = archer_get_dying_animation;
    c->get_walking_animation = archer_get_walking_animation;
    c->to_attack = archer_to_attack;
    c->attacking = archer_attacking;
    c->type_stats = archer_init(level);
    ent->type = c;
}


animation* archer_get_dying_animation(entity* ent){
    return get_animations()->archer_death;
}

animation* archer_get_walking_animation(entity* ent){
    return get_animations()->archer_walk;
}


void archer_attacking(entity* ent, game* g){
    if (!(ent->state == ENTITY_STATE_ATTACK_FAILING) && drawable_entity_get_frame(ent->drawable) == 12){
        switch (((archer*)ent->type->type_stats)->attack_type){
            case ARCHER_SHORT_HIT:
                ent->target->hp-=((archer*)ent->type->type_stats)->damage + ARCHER_SHORT_HIT_DAMAGE;
                break;
            case ARCHER_CRIT:
                game_add_projectile(g,arrow_create(ent->pos, ent->team, ent->facing, ARCHER_CRIT_DAMAGE));
            case ARCHER_NORMAL:
                game_add_projectile(g,arrow_create(ent->pos, ent->team, ent->facing, ARCHER_NORMAL_DAMAGE));
        }
    }
    drawable_entity_animation_forward(ent->drawable, ARCHER_BASE_ATTACK_SPEED/FPS);
}

int archer_get_current_range(entity* ent){
    archer* k = (archer*)(ent->type->type_stats);
    return k->range;
}

void archer_to_attack(entity* ent,entity* target){
    archer * player = ent->type->type_stats;
    ent->state = ENTITY_STATE_ATTACKING;
    animation_frame_destroy(ent->drawable->anim);
    ent->target = target;
    if (abs(ent->pos  - target->pos)<player->range_short){
        player->attack_type = ARCHER_SHORT_HIT;
        ent->drawable->anim = animation_frame_init(get_animations()->archer_short_hit);
    } else {
        if ((rand() % ARCHER_CRIT_CHANCE)) {
            player->attack_type = ARCHER_NORMAL;
            ent->drawable->anim = animation_frame_init(get_animations()->archer_hit);
        } else {
            player->attack_type = ARCHER_CRIT;
            ent->drawable->anim = animation_frame_init(get_animations()->archer_critical_hit);
        }
    }
}
