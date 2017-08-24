//
// Created by pierre on 22/08/17.
//
#include <SFML/Audio.h>
#include "controller.h"
#include "view.h"
#include "game_state.h"

void controller_process_events( game* g){
    sfVector2i mouse = sfMouse_getPositionRenderWindow(game_get_view_window(g));
    if (mouse.x>WINDOW_WIDTH-100.0){
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
                controller_process_mouse_click(g,mouse);
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


void controller_process_mouse_click(game* g, sfVector2i mouse){
    if (mouse.y>50 && mouse.y<150){
        team_launch_entity(g->player, g, mouse.x/100);
    }
    if ( mouse.y< 150) {
        if (mouse.x > 300 && mouse.x < 350) {
            game_order_retreat(g, 0);
        }
        if (mouse.x > 450 && mouse.x < 550) {
            game_order_assault(g, 0);
        }
    }
}
