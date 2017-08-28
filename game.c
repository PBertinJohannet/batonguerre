//
// Created by pierre on 21/08/17.
//

#include "game.h"
#include "entity_factory.h"
#include "stdio.h"
#include "stdlib.h"
#include "projectile.h"

game* game_init(game_state* state){
    game* g = malloc(sizeof(game));
    g->state = state;
    g->player = team_init(0);
    g->ennemy = team_init(1);
    g->view = view_init(state->window);
    g->entities = list_create();
    g->projectiles = list_create();
    g->frame = 0;
    g->controller = controller_init(g);
    game_init_teams(g);
    return g;
}

void game_init_teams(game* g){
    game_init_team(g,g->player);
    game_init_team(g,g->ennemy);
    g->ennemy_ai = dumb_ai_init(g->ennemy);
}
void game_init_team(game* g, team* t){
    team_init_brigades(t);
    entity* base = factory_new_entity(BASE,t,1,g);
    t->base = base;
    list_add(g->entities,base);
}
void game_add_entity(game* g, entity* ent){
    list_add(g->entities,ent);
}
void game_add_projectile(game* g, projectile* proj){
    list_add(g->projectiles,proj);
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
    for (int i =0;i<g->projectiles->size;i++){
        projectile* ent = (projectile*)(list_at(g->projectiles,i));
        list_add(drawables,ent->drawable);
    }
    return drawables;
}

void game_next_loop(game* g) {
    game_update(g);
    view_draw_map(g->view);
    view_draw_launchers(g->view, g->player->brigades);
    view_draw_gold(g->view, g->player->gold);
    view_draw_cursor(g->view, g->controller->commanding_brigade);
    view_draw_entities(g->view, game_get_drawables(g));
    if (g->player->base->hp < 1 ){
        playing_state_to_game_end_state(g->state, g->ennemy);
    }
    if (g->ennemy->base->hp < 1) {
        playing_state_to_game_end_state(g->state, g->player);
    }
}


team* game_get_team(game* g, int team_id){
    return !team_id?g->player:g->ennemy;
}

void game_update(game* g){
    g->frame+=1;
    dumb_ai_play(g->ennemy_ai, g);
    team_play(g->player, g->frame);
    team_play(g->ennemy, g->frame);
    controller_process_events( g->controller);
    for (int i =0;i<g->entities->size;i++){
        entity *ent = (entity *) (list_at(g->entities, i));
        ent->type->play(g, ent,g->entities);
        if (ent->state == ENTITY_STATE_DEAD){
            entity_destroy(ent);
            list_rm_at(g->entities,i);
            i--;
        }
    }
    for (int i =0;i<g->projectiles->size;i++){
        projectile* ent = (projectile*)(list_at(g->projectiles,i));
        if (ent->play(ent,g->entities)){
            list_rm_at(g->projectiles,i);
            i--;
        }
    }
}

void game_destroy(game* g){
    team_destroy(g->player);
    team_destroy(g->ennemy);
    list_free(g->entities, entity_destroy_void);
    view_destroy(g->view);
    dumb_ai_destroy(g->ennemy_ai);
}