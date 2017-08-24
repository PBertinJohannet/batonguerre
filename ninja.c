//
// Created by pierre on 22/08/17.
//

#include "ninja.h"

ninja* ninja_init(int level){
    ninja* k = malloc(sizeof(ninja));
    k->range = NINJA_RANGE;
    k->damage = level;
    k->attack_type = NINJA_NONE;
    return k;
}

void set_ninja_class(entity* ent, int level){
    entity_type* c = malloc(sizeof(entity_type));
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


void ninja_retreating(entity* ent, struct animation_list* anims){
    if (ent->drawable->anim->anim != anims->ninja_walk){
        animation_frame_destroy(ent->drawable->anim);
        ent->drawable->anim = animation_frame_init(anims->ninja_walk);
    }
    //int team_coeff = 1000*ent->stats->team + (2*ent->stats->team+1)*RETREAT_PLAYER;
    if ((int)(abs(ent->stats->pos-ent->stats->team*MAP_SIZE))>RETREAT_PLAYER){
        ent->stats->facing = !ent->stats->team;
        ent->stats->pos -= ent->stats->speed * (2 * ent->stats->facing - 1);
    } else {
        ent->stats->facing = ent->stats->team;
    }
}

void ninja_to_dying(entity* ent, struct animation_list* anims){
    ent->stats->state = DYING;
    ent->drawable->anim = animation_frame_init(anims->ninja_death);
}

void ninja_attack(entity* ent, game* g){
    if (!(ent->stats->state == ATTACK_FAILING) && ent->drawable->anim->frame == 12){
        int damage = NINJA_SLASH_DAMAGE;
        if (((kicker*)ent->type->type_stats)->attack_type == HIT){
            damage = NINJA_HIT_DAMAGE;
        }
        ent->target->stats->hp-=((kicker*)ent->type->type_stats)->damage + damage;

    }
}

int ninja_get_current_range(entity* ent){
    ninja* k = (ninja*)(ent->type->type_stats);
    return k->range;
}

void ninja_to_attack(entity* ent,entity* target, animation_list* anims){
    ent->stats->state = ATTACKING;
    animation_frame_destroy(ent->drawable->anim);
    ent->target = target;
    if (rand()%NINJA_HIT_CHANCE) {
        ((kicker *) (ent->type->type_stats))->attack_type = HIT;
        ent->drawable->anim = animation_frame_init(anims->ninja_strike);
    } else {
        ((kicker *) (ent->type->type_stats))->attack_type = SLASH;
        ent->drawable->anim = animation_frame_init(anims->ninja_slash);
    }
}

void ninja_to_aggro(entity* ent, animation_list* anims) {
    ent->stats->state = AGG_MOVING;
    animation_frame_destroy(ent->drawable->anim);
    ent->drawable->anim = animation_frame_init(anims->ninja_walk);
}