//
// Created by pierre on 21/08/17.
//

#include "game_state.h"
#include "entity_factory.h"
#include "stdio.h"
#include "object.h"
#include "level_reader.h"
#include "brigade_reader.h"
#include "base.h"
#include "counted_allocations.h"
#include "battle.h"
#include "battle_state.h"
battle* battle_from_level(game_state* state, char* level_name, char* camp_id){
    battle* g = counted_malloc(sizeof(battle), "battle create");
    g->state = state;
    level_reader* lvl = level_reader_init(level_name);
    battle_config* conf = level_reader_read_conf(lvl);
    g->ennemy = level_reader_read_team(lvl,1);
    g->player = level_reader_read_team(lvl,0);
    JSON_Object* player_save_brigades = json_value_get_object(json_parse_file(campaign_state_get_army_path(camp_id)));
    team_set_brigades(g->player, brigades_reader_get_brigades(player_save_brigades, g->player));
    g->view = view_init(state->window, conf);
    g->map_size = conf->map_size;
    g->entities = level_reader_read_entities(lvl, g);
    g->objects = level_reader_read_gold(lvl, g);
    g->controller = controller_init(g);
    battle_init_teams(g);
    g->ennemy_ai = level_reader_read_ai(lvl,g->ennemy);
    level_reader_destroy(lvl);
    g->campaign_id = camp_id;
    return g;
}

void battle_init_teams(battle* g){
    battle_init_team(g,g->player);
    battle_init_team(g,g->ennemy);
}
void battle_init_team(battle* g, team* t){
    entity* base = base_init(t->pop, 1250, t);
    set_base_class(base);
    t->base = base;
    list_add(g->entities,base);
}
void battle_add_entity(battle* g, entity* ent){
    list_add(g->entities,ent);
}
void battle_add_object(battle* g, object* proj){
    list_add(g->objects,proj);
}

 sfRenderWindow* battle_get_view_window(battle* g){
    return g->view->window;
}

list* battle_get_drawables(battle* g){
    list* drawables = list_init();
    for (unsigned int i =0;i<g->objects->size;i++){
        object* ent = (object*)(list_at(g->objects,i));
        list_add(drawables,ent->drawable);
    }
    for (unsigned int i =0;i<g->entities->size;i++){
        entity* ent = (entity*)(list_at(g->entities,i));
        list_add(drawables,ent->drawable);
    }
    return drawables;
}

void battle_draw(battle* g) {
    screen_drawer_clear(g->view->drawer);
    view_draw_map(g->view);
    view_draw_launchers(g->view, g->player->brigades);
    view_draw_gold(g->view, g->player->gold);
    view_draw_cursor(g->view, g->controller->commanding_brigade);
    view_draw_entities(g->view, battle_get_drawables(g));
    view_draw_perf(g->view, g->entities->size, g->objects->size);
}


void battle_update(battle* g){
    team_play(g->player);
    team_play(g->ennemy);
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
    for (unsigned int i =0;i<g->objects->size;i++){
        object* ent = (object*)(list_at(g->objects,i));
        if (ent->play(ent,g->entities)){
            object_destroy(ent);
            list_rm_at(g->objects,i);
            i--;
        }
    }
    if (g->player->base->hp < 1 ){
        battle_state_to_end_state(g->state, 0);
    }    else if (g->ennemy->base->hp < 1) {
        battle_state_to_end_state(g->state, 1);
    }
}


void battle_process_event(battle* b, sfEvent* e){
    controller_process_event(b->controller, e);
}

team* battle_get_team(battle* g, int team_id){
    return (team_id)?g->player:g->ennemy;
}

void battle_destroy(battle* g){
    team_destroy(g->player);
    team_destroy(g->ennemy);
    list_free(g->entities, entity_destroy_void);
    list_free(g->objects, (void(*)(void*))object_destroy);
    view_destroy(g->view);
    controller_destroy(g->controller);
    ai_destroy(g->ennemy_ai);
    counted_free(g, "freeing battle");
}