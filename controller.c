//
// Created by pierre on 22/08/17.
//
#include "controller.h"
#include "view.h"
#include "game_state.h"
#include "battle_interact.h"
#include "window_conf_reader.h"
#include "counted_allocations.h"
#include "battle_state.h"
controller* controller_init(battle* g){
    controller* c = counted_malloc(sizeof(controller), "controller init");
    c->commanding_brigade = 0;
    c->battle = g;
    return c;
}
void controller_process_event( controller* c, sfEvent* event){
    battle* g = c->battle;
    sfVector2i mouse = sfMouse_getPositionRenderWindow(battle_get_view_window(g));
    if (mouse.x>get_window_config()->window_width-100.0){
        view_move_right(g->view);
    } if (mouse.x<50.0) {
        view_move_left(g->view);
    }
    switch (event->type) {
        case sfEvtClosed:
            sfRenderWindow_close(battle_get_view_window(g));
            break;
        case sfEvtKeyPressed:

            if (sfKeyboard_isKeyPressed(sfKeySpace)){
                battle_state_to_paused_state(c->battle->state);
            } if (sfKeyboard_isKeyPressed(sfKeyRight)){
                view_move_right(g->view);
            } if (sfKeyboard_isKeyPressed(sfKeyLeft)){
                view_move_left(g->view);
            }

            break;
        case sfEvtMouseButtonPressed:
            controller_process_mouse_click(c,mouse);
            break;
        default:
            break;
    }
}


void controller_process_mouse_click(controller* c, sfVector2i mouse){
    battle* g = c->battle;
    if (mouse.x < 0 || mouse.y <0){
        return;
    }
    if (c->commanding_brigade){
        battle_command_one(g->player,
                         (unsigned int)(mouse.x*(1000.f/(float)get_window_config()->window_width))+g->view->camera_position,
                         c->selected_brigade);
        c->commanding_brigade = 0;
    }
    if (mouse.y>50 && mouse.y<150){
        if (sfKeyboard_isKeyPressed(sfKeyLControl)){
            c->commanding_brigade = 1;
            c->selected_brigade = (unsigned int)mouse.x / 100;
        } else {
            team_launch_entity(g->player, g, (unsigned int)mouse.x / 100);
        }
    }
    if ( mouse.y< 150) {
        if (mouse.x > 300 && mouse.x < 350) {
            battle_order_retreat(g->player);
        }
        if (mouse.x > 450 && mouse.x < 550) {
            battle_order_assault(g, g->player);
        }
    }
}



void controller_destroy(controller* c){
    counted_free(c, "destroying controller");
}