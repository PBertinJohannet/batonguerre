//
// Created by pierre on 21/08/17.
//

#include "game.h"
#include "entity_factory.h"
#include "stdio.h"
#include "stdlib.h"
game* game_init(game_state* state){
    game* g = malloc(sizeof(game));
    g->state = state;
    g->player = team_init(0);
    g->ennemy = team_init(1);
    g->anims = anims_load();
    g->view = view_init(state->window);
    g->entities = list_create();
    g->frame = 0;
    game_init_teams(g);
    return g;
}

void game_init_teams(game* g){
    game_init_team(g,g->player,0);
    game_init_team(g,g->ennemy,1);
    g->ennemy_ai = dumb_ai_init(g->ennemy);
}
void game_init_team(game* g, team* t, int team_id){
    team_init_spawners(t,g->anims, team_id);
    entity* base = factory_new_entity(BASE,team_id,1,g);
    t->base = base;
    list_add(g->entities,base);
}
void game_add_entity(game* g, entity* ent){
    list_add(g->entities,ent);
}

sfRenderWindow* game_get_view_window(game* g){
    return g->view->window;
}

list* game_get_drawables(game* g){
    list* drawables = list_create();
    for (int i =0;i<g->entities->size;i++){
        entity* ent = (entity*)(list_at(g->entities,i));
        list_add(drawables,ent->drawable);
    }
    return drawables;
}

void game_next_loop(game* g) {
    game_update(g);
    view_draw_map(g->view);
    view_draw_launchers(g->view, g->player->spawners);
    view_draw_gold(g->view, g->player->gold);
    view_draw_entities(g->view, game_get_drawables(g));
    if (g->player->base->stats->hp < 1 ){
        playing_state_to_game_end_state(g->state, g->ennemy);
    }
    if (g->ennemy->base->stats->hp < 1) {
        playing_state_to_game_end_state(g->state, g->player);
    }
}


team* game_get_team(game* g, int team_id){
    return !team_id?g->player:g->ennemy;
}

void game_order_retreat(game* g, int team_id){
    game_get_team(g,team_id)->order = RETREAT;
    for (int i =0;i<g->entities->size;i++) {
        entity *ent = (entity *) (list_at(g->entities, i));
        if (ent->stats->team == team_id) {
            ent->stats->state = RETREATING;
        }
    }
}
void game_order_assault(game* g, int team_id){
    game_get_team(g,team_id)->order = ATTACK;
    for (int i =0;i<g->entities->size;i++) {
        entity *ent = (entity *) (list_at(g->entities, i));
        if (ent->stats->team == team_id) {
            ent->stats->state = AGG_MOVING;
        }
    }
}

void game_update(game* g){
    g->frame+=1;
    dumb_ai_play(g->ennemy_ai, g);
    team_play(g->player, g->frame);
    team_play(g->ennemy, g->frame);
    controller_process_events( g);
    for (int i =0;i<g->entities->size;i++){
        entity* ent = (entity*)(list_at(g->entities,i));
        if (ent->type->play(ent,g->entities, g->anims)){
            list_rm_at(g->entities,i);
            i--;
        }
    }
}

void game_destroy(game* g){
    team_destroy(g->player);
    team_destroy(g->ennemy);
    animation_list_destroy(g->anims);
    list_free(g->entities, entity_destroy_void);
    view_destroy(g->view);
    dumb_ai_destroy(g->ennemy_ai);
}