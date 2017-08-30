//
// Created by pierre on 21/08/17.
//

#include "entity_behaviour.h"
#include "game.h"
#include "math.h"
#include "command.h"
#include "brigade.h"
#include "window_conf_reader.h"

void set_basic_behaviour(entity_behaviour* behaviour){
    behaviour->attack_failing = entity_base_attack_failing;
    behaviour->dying = entity_base_dying;
    behaviour->assaulting = entity_base_assaulting;
    behaviour->retreating = entity_base_retreating;
    behaviour->to_assault = entity_base_to_assault;
    behaviour->to_retreat = entity_base_to_retreat;
    behaviour->play = entity_base_play;
    behaviour->to_dying = entity_base_to_dying;
}


void entity_base_assaulting(entity* player, list* entities){
    if (!entity_base_find_target(player, entities)) {
        int target = entity_get_command(player)->target;
        if ((int)(abs(player->pos-target))>player->speed){
            player->facing = player->pos>target;
            player->pos -= player->speed * (2 * player->facing - 1);
        } else {
            player->facing = player->team->id;
            player->pos = entity_get_command(player)->target;
        }
        drawable_entity_animation_forward(player->drawable, 25.0/get_window_config()->fps);
    }
}


int entity_base_find_target(entity* player, list* entities){
    int range = player->type->get_current_range(player);
    list* in_range = list_create();
    for (int i = 0; i < entities->size; i++) {
        entity *ent = (entity *) list_at(entities, i);
        if (player->team != ent->team
            && abs(player->pos - ent->pos) < range
            && ent->state != ENTITY_STATE_DYING) {
            list_add(in_range,ent);
        }
    }
    if (in_range->size>0){
        player->type->to_attack(player, list_random(in_range));
        list_destroy(in_range);
        return 1;
    }
    list_destroy(in_range);
    return 0;
}



void entity_base_dying(entity* player){
    if (drawable_entity_get_frame(player->drawable)== player->drawable->anim->anim->nb_frames - 1){
        player->state = ENTITY_STATE_DEAD;
    }
    drawable_entity_animation_forward(player->drawable, 20.0/get_window_config()->fps);
}



void entity_base_attack_failing(entity* player, list* entities){
    if (drawable_entity_get_frame(player->drawable) == player->drawable->anim->anim->nb_frames - 1) {
        player->type->to_assault(player);
    }
    drawable_entity_animation_forward(player->drawable, 25.0/get_window_config()->fps);
}

void entity_base_to_retreat(entity* player){
    animation_frame_destroy(player->drawable->anim);
    player->drawable->anim = animation_frame_init( player->type->get_walking_animation(player));
    player->state = ENTITY_STATE_RETREATING;
}


void entity_base_retreating(entity* player, list* entities){
    if ((int)(abs(player->pos-player->team->id*player->team->pop))>50){
        player->facing = !player->team->id;
        player->pos -= player->speed * (2 * player->facing - 1) ;
    } else {
        player->facing = player->team->id;
        entity_base_find_target(player, entities);
    }
    drawable_entity_animation_forward(player->drawable, 25.0/get_window_config()->fps);
}

void entity_base_to_dying(entity* player){
    animation_frame_destroy(player->drawable->anim);
    player->drawable->anim = animation_frame_init( player->type->get_dying_animation(player));
    player->state = ENTITY_STATE_DYING;
}


void entity_base_to_assault(entity* player){
    animation_frame_destroy(player->drawable->anim);
    player->drawable->anim = animation_frame_init( player->type->get_walking_animation(player));
    player->state = ENTITY_STATE_ASSAULT;
}



void entity_base_play(game* g, entity* player, list* entities){
    if (player->state != ENTITY_STATE_DYING && player->hp<1){
        player->type->to_dying(player);
        return;
    }
    command* c = entity_get_command(player);
    if (player->state != ENTITY_STATE_ATTACKING && player->state != ENTITY_STATE_DYING) {
        switch (c->entity_state) {
            case ENTITY_STATE_RETREATING:
                if (player->state != ENTITY_STATE_RETREATING) {
                    player->type->to_retreat(player);
                }
                break;
            case ENTITY_STATE_ASSAULT:
                if (player->state == ENTITY_STATE_RETREATING) {
                    player->type->to_assault(player);
                }
                break;
        }
    }
    switch (player->state) {
        case ENTITY_STATE_RETREATING:
            player->type->retreating(player, entities);
            break;
        case ENTITY_STATE_ASSAULT:
            player->type->assaulting(player, entities);
            break;
        case ENTITY_STATE_ATTACKING:
            if (drawable_entity_get_frame(player->drawable)== player->drawable->anim->anim->nb_frames - 1) {
                player->type->to_assault(player);
            } else if (player->target->state == ENTITY_STATE_DYING){
                player->state = ENTITY_STATE_ATTACK_FAILING;
            }
            player->type->attacking(player, g);
            break;
        case ENTITY_STATE_DYING:
            player->type->dying(player);
            break;
        case ENTITY_STATE_ATTACK_FAILING:
            player->type->attack_failing(player, entities);
        default:
            break;
    }
}


void entity_behaviour_destroy(entity_behaviour* ent){
    free(ent->type_stats);
    free(ent);
}