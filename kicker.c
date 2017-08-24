//
// Created by pierre on 22/08/17.
//
#include "kicker.h"
#include "time.h"
kicker* kicker_init(int level){
    kicker* k = malloc(sizeof(kicker));
    k->range = KICKER_RANGE;
    k->damage = level;
    k->attack_type = KICKER_NONE;
    return k;
}

void set_kicker_class(entity* ent, int level){
    entity_type* c = malloc(sizeof(entity_type));
    c->type_stats = kicker_init(level);
    c->play = entity_base_play;
    c->get_current_range = kicker_get_current_range;
    c->to_attack = kicker_to_attack;
    c->to_aggro = kicker_to_aggro;
    c->attack = kicker_attack;
    c->to_dying = kicker_to_dying;
    c->retreating = kicker_retreating;
    ent->type = c;
}

void kicker_retreating(entity* ent, struct animation_list* anims){
    if (ent->drawable->anim->anim != anims->stick_walk){
        animation_frame_destroy(ent->drawable->anim);
        ent->drawable->anim = animation_frame_init(anims->stick_walk);
    }
    //int team_coeff = 1000*ent->stats->team - (2*ent->stats->team+1)*RETREAT_PLAYER;
    if ((int)(abs(ent->stats->pos-ent->stats->team*MAP_SIZE))>RETREAT_PLAYER){
        ent->stats->facing = !ent->stats->team;
        ent->stats->pos -= ent->stats->speed * (2 * ent->stats->facing - 1) ;
    } else {
        ent->stats->facing = ent->stats->team;
    }
}


void kicker_to_dying(entity* ent, struct animation_list* anims){
    ent->stats->state = DYING;
    animation_frame* new_anim;
    if (ent->stats->state == AGG_MOVING
        || ent->drawable->anim->frame < 6
        || ent->drawable->anim->frame > 16){
        new_anim = animation_frame_init(anims->stick_walk_death);
        ent->stats->pos += 60 * (ent->stats->facing * 2 - 1);
    } else {
        new_anim = animation_frame_init(anims->stick_kick_death);
        new_anim->frame = ent->drawable->anim->frame;
    }
    animation_frame_destroy(ent->drawable->anim);
    ent->drawable->anim = new_anim;
}

void kicker_attack(entity* ent, game* g){
    if (!(ent->stats->state == ATTACK_FAILING) && ent->drawable->anim->frame == 11){
        int damage = KICKER_KICK_DAMAGE;
        if (((kicker*)ent->type->type_stats)->attack_type == PUNCH){
            damage = KICKER_PUNCH_DAMAGE;
        }
        ent->target->stats->hp-=((kicker*)ent->type->type_stats)->damage + damage;

    }
}

int kicker_get_current_range(entity* ent){
    kicker* k = (kicker*)(ent->type->type_stats);
    return k->range;
}

void kicker_to_attack(entity* ent,entity* target, animation_list* anims){
    ent->stats->state = ATTACKING;
    animation_frame_destroy(ent->drawable->anim);
    ent->target = target;
    if (rand()%KICKER_PUNCH_CHANCE) {
        ((kicker *) (ent->type->type_stats))->attack_type = PUNCH;
        ent->drawable->anim = animation_frame_init(anims->kicker_punch);
    } else {
        ((kicker *) (ent->type->type_stats))->attack_type = KICK;
        ent->drawable->anim = animation_frame_init(anims->stick_kick);
    }
}

void kicker_to_aggro(entity* ent, animation_list* anims){
    ent->stats->state = AGG_MOVING;
    animation_frame_destroy(ent->drawable->anim);
    ent->drawable->anim = animation_frame_init(anims->stick_walk);
}