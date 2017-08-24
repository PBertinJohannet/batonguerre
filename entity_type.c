//
// Created by pierre on 21/08/17.
//

#include "entity_type.h"
#include "game.h"
#include "math.h"

int entity_base_agg_moving(entity* player, list* entities, animation_list* anims){
    int range = player->type->get_current_range(player);
    list* in_range = list_create();
    for (int i = 0; i < entities->size; i++) {
        entity *ent = (entity *) list_at(entities, i);
        if (player->stats->team != ent->stats->team
            && abs(player->stats->pos - ent->stats->pos) < range
            && ent->stats->state != DYING) {
            list_add(in_range,ent);
        }
    }
    if (in_range->size>0){
        player->type->to_attack(player, list_random(in_range), anims);
        list_destroy(in_range);
        return 0;
    }
    list_destroy(in_range);
    player->stats->facing = player->stats->team;
    player->stats->pos -= player->stats->speed * (2 * player->stats->facing - 1);
    return 0;
}


int entity_base_attack(game* g, entity* player, list* entities, animation_list* anims){
    if (player->drawable->anim->frame == player->drawable->anim->anim->nb_frames - 1) {
        player->type->to_aggro(player, anims);
    } else if (player->target->stats->state == DYING){
        player->stats->state = ATTACK_FAILING;
    }
    player->type->attack(player, g);
    return 0;
}


int entity_base_dying(entity* player, list* entities, animation_list* anims){
    if (player->drawable->anim->frame == player->drawable->anim->anim->nb_frames - 1){
        entity_destroy(player);
        return 1;
    }
    return 0;
}


int entity_base_attack_failing(entity* player, list* entities, animation_list* anims){
    if (player->drawable->anim->frame == player->drawable->anim->anim->nb_frames - 1) {
        player->type->to_aggro(player, anims);
    }
    return 0;
}

int entity_base_retreat(entity* player, list* entities, animation_list* anims){
    player->type->retreating(player, anims);
    return 0;
}


int entity_base_play(game* g, entity* player, list* entities, animation_list* anims){
    if (player->stats->state != DYING && player->stats->hp<1){
        player->type->to_dying(player, anims);
        return 0;
    }
    switch (player->stats->state) {
        case RETREATING:
            return entity_base_retreat(player, entities, anims);
        case AGG_MOVING:
            return entity_base_agg_moving(player, entities, anims);
        case ATTACKING:
            return entity_base_attack(g, player, entities, anims);
        case DYING:
            return entity_base_dying(player, entities, anims);
        case ATTACK_FAILING:
            return entity_base_attack_failing(player, entities, anims);
        default:
            break;
    }
    return 0;
}


void entity_type_destroy(entity_type* ent){
    free(ent->type_stats);
    free(ent);
}