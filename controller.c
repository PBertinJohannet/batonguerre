//
// Created by pierre on 22/08/17.
//
#include <SFML/Audio.h>
#include "controller.h"
#include "view.h"
#include "game_state.h"
#include "game_interact.h"
#include "window_conf_reader.h"
controller* controller_init(game* g){
    controller* c = malloc(sizeof(controller));
    c->commanding_brigade = 0;
    c->game = g;
    return c;
}
void controller_process_events( controller* c){
    game* g = c->game;
    sfVector2i mouse = sfMouse_getPositionRenderWindow(game_get_view_window(g));
    if (mouse.x>get_window_config()->window_width-100.0){
        view_move_right(g->view);
    } if (mouse.x<50.0) {
        view_move_left(g->view);
    }
    int to_paused = 0;
    sfEvent* event = malloc(sizeof(sfEvent));
    while (sfRenderWindow_pollEvent(game_get_view_window(g), event)) {
        switch (event->type) {
            case sfEvtClosed:
                sfRenderWindow_close(game_get_view_window(g));
                break;
            case sfEvtKeyPressed:

                if (sfKeyboard_isKeyPressed(sfKeySpace)){
                    to_paused = 1;
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
    free(event);
    if (to_paused) {
        playing_state_to_paused_state(g->state);
    }
}


void controller_process_mouse_click(controller* c, sfVector2i mouse){
    game* g = c->game;
    if (c->commanding_brigade){
        game_command_one(g,g->player,mouse.x*1000/get_window_config()->window_width+g->view->camera_position, c->selected_brigade);
        c->commanding_brigade = 0;
    }
    if (mouse.y>50 && mouse.y<150){
        if (sfKeyboard_isKeyPressed(sfKeyLControl)){
            c->commanding_brigade = 1;
            c->selected_brigade = mouse.x / 100;
        } else {
            team_launch_entity(g->player, g, mouse.x / 100);
        }
    }
    if ( mouse.y< 150) {
        if (mouse.x > 300 && mouse.x < 350) {
            game_order_retreat(g, g->player);
        }
        if (mouse.x > 450 && mouse.x < 550) {
            game_order_assault(g, g->player);
        }
    }
}
