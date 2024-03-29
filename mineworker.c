
#include "mineworker.h"
#include "time.h"
#include "global.h"
#include "window_conf_reader.h"
#include "brigade_reader.h"
#include "counted_allocations.h"
#include "gold_heap.h"
#include "math.h"
#include "stdlib.h"
void set_mineworker_class(entity* ent){
    entity_behaviour* c = counted_malloc(sizeof(entity_behaviour), "create mineworker behaviour");
    set_basic_behaviour(c);
    c->type =MINEWORKER;
    c->get_current_range = mineworker_get_current_range;
    c->get_dying_animation = mineworker_get_dying_animation;
    c->get_walking_animation = mineworker_get_walking_animation;
    c->to_attack = mineworker_to_attack;
    c->attacking = mineworker_attacking;
    c->assaulting = mineworker_assaulting;
    c->retreating = mineworker_retreating;
    mineworker_current_state* current_state = counted_malloc(sizeof(mineworker_current_state), "creating mineworker gold_state");
    current_state->gold_harvested = 0;
    current_state->is_harvesting = 0;
    current_state->targeted_heap = (void*)0;
    c->current_state = current_state;
    ent->type = c;
    ent->drawable = drawable_entity_init(animation_frame_init(get_animations()->mineworker_walk),
                                         &ent->pos, &ent->facing, ent->brigade->base_size);
}



void mineworker_retreating(entity* player,list* entities ){
    mineworker_returning_gold(player);
}


void mineworker_assaulting(entity* player, list* entities, list* objects){
    mineworker_current_state* state = player->type->current_state;
    mineworker_stats* stats = player->brigade->specific_stats;
    if (state->is_harvesting){
        mineworker_harvesting(player);
    } else if (state->gold_harvested >= stats->max_gold){
         mineworker_returning_gold(player);
    } else if (!mineworker_find_target(player, objects)) {
        unsigned int target = entity_get_command(player)->target;
        if ((int)(abs(player->pos-target))>player->speed*get_elapsed_sec()){
            player->facing = (unsigned int)(player->pos > target);
            player->pos -= player->speed*get_elapsed_sec() * (2.0 * (float)player->facing - 1.0);
        } else {
            player->facing = player->team->id;
            player->pos = entity_get_command(player)->target;
        }
        drawable_entity_animation_forward(player->drawable, 25.0*get_elapsed_sec());
    }
}

void mineworker_returning_gold(entity* player){
    unsigned int target = player->team->base->pos;
    if ((int)(abs(player->pos-target))>player->speed*get_elapsed_sec()){
        player->facing = (unsigned int)(player->pos > target);
        player->pos -= player->speed*get_elapsed_sec() * (2.0 * (float)player->facing - 1.0);
    } else {
        player->facing = player->team->id;
        player->pos = target;
        mineworker_current_state* state = player->type->current_state;
        player->team->gold +=  state->gold_harvested;
        state->gold_harvested = 0;
    }
    drawable_entity_animation_forward(player->drawable, 25.0*get_elapsed_sec());
}

int mineworker_find_target(entity* player, list* objects){
    int range = player->type->get_current_range(player);
    list* in_range = list_init();
    for (unsigned int i = 0; i < objects->size; i++) {
        object *obj = (object *) list_at(objects, i);
        if (obj->object_type == OBJECT_GOLD_HEAP && abs(obj->pos - player->pos)<range) {
            if (((gold_heap*)(obj->self))->dying==HEAP_DYING_FRAMES) {
                list_add(in_range, obj);
            }
        }
    }
    if (in_range->size>0){
        mineworker_to_harvest(player, list_random(in_range));
        list_destroy(in_range);
        return 1;
    }
    list_destroy(in_range);
    return 0;
}


animation* mineworker_get_dying_animation(entity* ent){
    return get_animations()->stick_walk_death;
}

animation* mineworker_get_walking_animation(entity* ent){
    return get_animations()->mineworker_walk;
}


void mineworker_attacking(entity* ent, battle* g){
    ent->pos = 0;
    printf("mineworker cant attack ! \n");
    exit(0);
}
void mineworker_harvesting(entity* ent){
    mineworker_current_state* state = ent->type->current_state;
    mineworker_stats* stats = ent->brigade->specific_stats;
    gold_heap* heap = state->targeted_heap->self;
    if (heap->gold_current<1 ||
        (unsigned int) (ent->drawable->anim->frame) == ent->drawable->anim->anim->nb_frames-1 ||
            heap->dying<HEAP_DYING_FRAMES){
        state->is_harvesting = 0;
        state->targeted_heap = 0;
        animation_frame_destroy(ent->drawable->anim);
        ent->drawable->anim = animation_frame_init(get_animations()->mineworker_walk);
        ent->state = ENTITY_STATE_ASSAULT;
    } else {
        float advancing_frame = (float)stats->harvesting_speed*get_elapsed_sec();
        ent->drawable->anim->frame+=advancing_frame;
        if (ent->drawable->anim->frame-advancing_frame < 35.f && ent->drawable->anim->frame > 35.f){
            state->gold_harvested+=stats->gold_harvested;
            heap->gold_current-=1;
        }
    }
}

int mineworker_get_current_range(entity* ent){
    mineworker_stats* k = (mineworker_stats*)(ent->brigade->specific_stats);
    return k->range;
}

void mineworker_to_harvest(entity* ent,object* target){
    mineworker_current_state* state = ent->type->current_state;
    state->is_harvesting = 1;
    state->targeted_heap = target;
    animation_frame_destroy(ent->drawable->anim);
    ent->drawable->anim = animation_frame_init(get_animations()->mining);
}
void mineworker_to_attack(entity* ent,entity* target){
    printf("mineworker cant attack ! \n");
    exit(0);
}
