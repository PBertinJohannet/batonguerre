//
// Created by pierre on 22/08/17.
//
#include "kicker.h"
#include "time.h"
#include "global.h"
kicker* kicker_init(int level){
    kicker* k = malloc(sizeof(kicker));
    k->range = KICKER_RANGE;
    k->attack_type = KICKER_NONE;
    return k;
}

void set_kicker_class(entity* ent, int level){
    entity_behaviour* c = malloc(sizeof(entity_behaviour));
    set_basic_behaviour(c);
    c->type =KICKER;
    c->get_current_range = kicker_get_current_range;
    c->get_dying_animation = kicker_get_dying_animation;
    c->get_walking_animation = kicker_get_walking_animation;
    c->to_attack = kicker_to_attack;
    c->attacking = kicker_attacking;
    c->type_stats = kicker_init(level);
    ent->type = c;
}

animation* kicker_get_dying_animation(entity* ent){
    if (ent->state == ENTITY_STATE_ASSAULT
        || ent->drawable->anim->frame < 6
        || ent->drawable->anim->frame > 16){
        return get_animations()->stick_walk_death;
    }
    return get_animations()->stick_kick_death;
}

animation* kicker_get_walking_animation(entity* ent){
    return get_animations()->stick_walk;
}


void kicker_attacking(entity* ent, game* g){
    float base_attack_speed = (((kicker*)ent->type->type_stats)->attack_type == PUNCH)?KICKER_PUNCH_SPEED:KICKER_BASE_ATTACK_SPEED;
    if (!(ent->state == ENTITY_STATE_ATTACK_FAILING) && drawable_entity_get_frame(ent->drawable) == 11){
        int damage = KICKER_KICK_DAMAGE;
        if (((kicker*)ent->type->type_stats)->attack_type == PUNCH){
            damage = KICKER_PUNCH_DAMAGE;
        }
        ent->target->hp-= damage;
    }
    drawable_entity_animation_forward(ent->drawable, base_attack_speed/FPS);
}

int kicker_get_current_range(entity* ent){
    kicker* k = (kicker*)(ent->type->type_stats);
    return k->range;
}

void kicker_to_attack(entity* ent,entity* target){
    ent->state = ENTITY_STATE_ATTACKING;
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
