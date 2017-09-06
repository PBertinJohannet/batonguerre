//
// Created by pierre on 21/08/17.
//

#include "game_state.h"
#include "entity_factory.h"
#include "stdio.h"
#include "projectile.h"
#include "level_reader.h"
#include "brigade_reader.h"
#include "base.h"
#include "counted_allocations.h"
#include "battle_state.h"
battle_state* battle_state_from_level(game_state* state, char* level_name,__attribute__ ((unused)) char* saved_battle_state){
    battle_state* g = counted_malloc(sizeof(battle_state), "battle_state create");
    g->state = state;
    level_reader* lvl = level_reader_init(level_name);
    battle_state_config* conf = level_reader_read_conf(lvl);
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
    battle_state_init_teams(g);
    g->ennemy_ai = level_reader_read_ai(lvl,g->ennemy);
    return g;
}

void battle_state_init_teams(battle_state* g){
    battle_state_init_team(g,g->player);
    battle_state_init_team(g,g->ennemy);
}
void battle_state_init_team(battle_state* g, team* t){
    entity* base = base_init(t->pop, 250, t);
    set_base_class(base);
    t->base = base;
    list_add(g->entities,base);
}
void battle_state_add_entity(battle_state* g, entity* ent){
    list_add(g->entities,ent);
}
void battle_state_add_projectile(battle_state* g, projectile* proj){
    list_add(g->projectiles,proj);
}

__attribute__ ((pure)) sfRenderWindow* battle_state_get_view_window(battle_state* g){
    return g->view->window;
}

list* battle_state_get_drawables(battle_state* g){
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

void battle_state_draw(battle_state* g) {
    battle_state_update(g);
    view_draw_map(g->view);
    view_draw_launchers(g->view, g->player->brigades);
    view_draw_gold(g->view, g->player->gold);
    view_draw_cursor(g->view, g->controller->commanding_brigade);
    view_draw_entities(g->view, battle_state_get_drawables(g));
}


void battle_state_update(battle_state* g){
    g->frame+=1;
    team_play(g->player, g->frame);
    team_play(g->ennemy, g->frame);
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
    if (g->player->base->hp < 1 ){
        battle_state_to_battle_state(g->state, g->ennemy);
    }
    if (g->ennemy->base->hp < 1) {
        battle_state_to_battle_state(g->state, g->player);
    }
}




void battle_state_destroy(battle_state* g){
    team_destroy(g->player);
    team_destroy(g->ennemy);
    list_free(g->entities, entity_destroy_void);
    view_destroy(g->view);
    //dumb_ai_destroy(g->ennemy_ai);
}