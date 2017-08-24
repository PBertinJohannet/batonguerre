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
    entity_type* c = malloc(sizeof(entity_type));
    c->type_stats = archer_init(level);
    c->play = entity_base_play;
    c->get_current_range = archer_get_current_range;
    c->to_attack = archer_to_attack;
    c->to_aggro = archer_to_aggro;
    c->attack = archer_attack;
    c->to_dying = archer_to_dying;
    c->retreating = archer_retreating;
    ent->type = c;
}


void archer_retreating(entity* ent){
    if (ent->drawable->anim->anim != get_animations()->archer_walk){
        animation_frame_destroy(ent->drawable->anim);
        ent->drawable->anim = animation_frame_init(get_animations()->archer_walk);
    }
    if ((int)(abs(ent->pos-ent->team*MAP_SIZE))>RETREAT_PLAYER){
        ent->facing = !ent->team;
        ent->pos -= ent->speed * (2 * ent->facing - 1);
    } else {
        ent->facing = ent->team;
    }
}

void archer_to_dying(entity* ent){
    ent->state = DYING;
    ent->drawable->anim = animation_frame_init(get_animations()->archer_death);
}

void archer_attack(entity* ent, game* g){
    if (!(ent->state == ATTACK_FAILING) && ent->drawable->anim->frame == 12){
        switch (((kicker*)ent->type->type_stats)->attack_type){
            case ARCHER_SHORT_HIT:
                ent->target->hp-=((archer*)ent->type->type_stats)->damage + ARCHER_SHORT_HIT_DAMAGE;
                break;
            case ARCHER_CRIT:
                game_add_projectile(g,arrow_create(ent->pos, ent->team, ent->facing, ARCHER_CRIT_DAMAGE));
            case ARCHER_NORMAL:
                game_add_projectile(g,arrow_create(ent->pos, ent->team, ent->facing, ARCHER_NORMAL_DAMAGE));
        }
    }
}

int archer_get_current_range(entity* ent){
    archer* k = (archer*)(ent->type->type_stats);
    return k->range;
}

void archer_to_attack(entity* ent,entity* target){
    archer * player = ent->type->type_stats;
    ent->state = ATTACKING;
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

void archer_to_aggro(entity* ent) {
    ent->state = AGG_MOVING;
    animation_frame_destroy(ent->drawable->anim);
    ent->drawable->anim = animation_frame_init(get_animations()->archer_walk);
}