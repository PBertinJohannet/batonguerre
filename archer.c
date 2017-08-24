//
// Created by pierre on 24/08/17.
//


#include "archer.h"

archer* archer_init(int level){
    archer* k = malloc(sizeof(archer));
    k->range = 400;
    k->range_short = 40;
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


void archer_retreating(entity* ent, struct animation_list* anims){
    if (ent->drawable->anim->anim != anims->archer_walk){
        animation_frame_destroy(ent->drawable->anim);
        ent->drawable->anim = animation_frame_init(anims->archer_walk);
    }
    if ((int)(abs(ent->stats->pos-ent->stats->team*MAP_SIZE))>RETREAT_PLAYER){
        ent->stats->facing = !ent->stats->team;
        ent->stats->pos -= ent->stats->speed * (2 * ent->stats->facing - 1);
    } else {
        ent->stats->facing = ent->stats->team;
    }
}

void archer_to_dying(entity* ent, struct animation_list* anims){
    ent->stats->state = DYING;
    ent->drawable->anim = animation_frame_init(anims->archer_death);
}

void archer_attack(entity* ent){
    if (!(ent->stats->state == ATTACK_FAILING) && ent->drawable->anim->frame == 12){
        int damage = ARCHER_NORMAL_DAMAGE;
        if (((kicker*)ent->type->type_stats)->attack_type == ARCHER_SHORT_HIT){
            damage = ARCHER_SHORT_HIT_DAMAGE;
        } else if (((kicker*)ent->type->type_stats)->attack_type == ARCHER_CRIT){
            damage = ARCHER_CRIT_DAMAGE;
        }
        ent->target->stats->hp-=((archer*)ent->type->type_stats)->damage + damage;

    }
}

int archer_get_current_range(entity* ent){
    archer* k = (archer*)(ent->type->type_stats);
    return k->range;
}

void archer_to_attack(entity* ent,entity* target, animation_list* anims){
    archer * player = ent->type->type_stats;
    ent->stats->state = ATTACKING;
    printf("target : %p\n", target);
    animation_frame_destroy(ent->drawable->anim);
    ent->target = target;
    if (abs(ent->stats->pos  - target->stats->pos)<player->range_short){
        player->attack_type = ARCHER_SHORT_HIT;
        ent->drawable->anim = animation_frame_init(anims->archer_short_hit);
    } else {
        if ((rand() % ARCHER_CRIT_CHANCE)) {
            player->attack_type = ARCHER_NORMAL;
            ent->drawable->anim = animation_frame_init(anims->archer_hit);
        } else {
            player->attack_type = ARCHER_CRIT;
            ent->drawable->anim = animation_frame_init(anims->archer_critical_hit);
        }
    }
}

void archer_to_aggro(entity* ent, animation_list* anims) {
    ent->stats->state = AGG_MOVING;
    animation_frame_destroy(ent->drawable->anim);
    ent->drawable->anim = animation_frame_init(anims->archer_walk);
}