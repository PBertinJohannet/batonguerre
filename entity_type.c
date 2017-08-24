//
// Created by pierre on 21/08/17.
//

#include "entity_type.h"
#include "game.h"
#include "math.h"

int entity_base_agg_moving(entity* player, list* entities){
    int range = player->type->get_current_range(player);
    list* in_range = list_create();
    for (int i = 0; i < entities->size; i++) {
        entity *ent = (entity *) list_at(entities, i);
        if (player->team != ent->team
            && abs(player->pos - ent->pos) < range
            && ent->state != DYING) {
            list_add(in_range,ent);
        }
    }
    if (in_range->size>0){
        player->type->to_attack(player, list_random(in_range));
        list_destroy(in_range);
        return 0;
    }
    list_destroy(in_range);
    player->facing = player->team;
    player->pos -= player->speed * (2 * player->facing - 1);
    return 0;
}


int entity_base_attack(game* g, entity* player, list* entities){
    if (player->drawable->anim->frame == player->drawable->anim->anim->nb_frames - 1) {
        player->type->to_aggro(player);
    } else if (player->target->state == DYING){
        player->state = ATTACK_FAILING;
    }
    player->type->attack(player, g);
    return 0;
}


int entity_base_dying(entity* player, list* entities){
    if (player->drawable->anim->frame == player->drawable->anim->anim->nb_frames - 1){
        entity_destroy(player);
        return 1;
    }
    return 0;
}


int entity_base_attack_failing(entity* player, list* entities){
    if (player->drawable->anim->frame == player->drawable->anim->anim->nb_frames - 1) {
        player->type->to_aggro(player);
    }
    return 0;
}

int entity_base_retreat(entity* player, list* entities){
    player->type->retreating(player);
    return 0;
}


int entity_base_play(game* g, entity* player, list* entities){
    if (player->state != DYING && player->hp<1){
        player->type->to_dying(player);
        return 0;
    }
    switch (player->state) {
        case RETREATING:
            return entity_base_retreat(player, entities);
        case AGG_MOVING:
            return entity_base_agg_moving(player, entities);
        case ATTACKING:
            return entity_base_attack(g, player, entities);
        case DYING:
            return entity_base_dying(player, entities);
        case ATTACK_FAILING:
            return entity_base_attack_failing(player, entities);
        default:
            break;
    }
    return 0;
}


void entity_type_destroy(entity_type* ent){
    free(ent->type_stats);
    free(ent);
}