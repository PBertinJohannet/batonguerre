//
// Created by pierre on 21/08/17.
//

#include "game.h"
#include "entity_factory.h"
#include "stdio.h"
#include "projectile.h"
#include "level_reader.h"
#include "brigade_reader.h"
#include "base.h"
#include "counted_allocations.h"
game* game_from_level(game_state* state, char* level_name,__attribute__ ((unused)) char* saved_game){
    game* g = counted_malloc(sizeof(game), "game create");
    g->state = state;
    level_reader* lvl = level_reader_init(level_name);
    battle_config* conf = level_reader_read_conf(lvl);
    g->ennemy = level_reader_read_team(lvl,1);
    g->player = level_reader_read_team(lvl,0);
    json_t* player_save_brigades = start_json("confs/saves/01/army.json");
    team_set_brigades(g->player, brigades_reader_get_brigades(player_save_brigades, g->player));
    g->view = view_init(state->window, conf);
    g->entities = list_create();
    g->projectiles = list_create();
    g->frame = 0;
    g->map_size = conf->map_size;
    g->controller = controller_init(g);
    game_init_teams(g);
    g->ennemy_ai = level_reader_read_ai(lvl,g->ennemy);
    return g;
}

void game_init_teams(game* g){
    game_init_team(g,g->player);
    game_init_team(g,g->ennemy);
}
void game_init_team(game* g, team* t){
    entity* base = base_init(t->pop, 250, t);
    set_base_class(base);
    t->base = base;
    list_add(g->entities,base);
}
void game_add_entity(game* g, entity* ent){
    list_add(g->entities,ent);
}
void game_add_projectile(game* g, projectile* proj){
    list_add(g->projectiles,proj);
}

__attribute__ ((pure)) sfRenderWindow* game_get_view_window(game* g){
    return g->view->window;
}

list* game_get_drawables(game* g){
    list* drawables = list_create();
    for (unsigned int i =0;i<g->entities->size;i++){
        entity* ent = (entity*)(list_at(g->entities,i));
        list_add(drawables,ent->drawable);
    }
    for (unsigned int i =0;i<g->projectiles->size;i++){
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


void game_update(game* g){
    g->frame+=1;
    team_play(g->player, g->frame);
    team_play(g->ennemy, g->frame);
    controller_process_events( g->controller);
    g->ennemy_ai->play(g->ennemy_ai, g);
    for (unsigned int i =0;i<g->entities->size;i++){
        entity *ent = (entity *) (list_at(g->entities, i));
        ent->type->play(g, ent,g->entities);
        if (ent->state == ENTITY_STATE_DEAD){
            entity_destroy(ent);
            list_rm_at(g->entities,i);
            i--;
        }
    }
    for (unsigned int i =0;i<g->projectiles->size;i++){
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
    //dumb_ai_destroy(g->ennemy_ai);
}