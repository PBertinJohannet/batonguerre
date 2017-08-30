//
// Created by pierre on 23/08/17.
//
#include "paused_state.h"
#include "window_conf_reader.h"
void paused_game_display_message(paused_state* g){
    view* v = g->paused_game->view;
    sfText_destroy(v->text);
    v->text = sfText_create();
    sfText_setString(v->text, " PAUSED \n press SPACE to continue ");
    window_config* win_conf = get_window_config();
    sfVector2f position = {win_conf->window_height/4, win_conf->window_width/4};
    sfText_setPosition(v->text, position);
    sfText_setFont(v->text, v->font);
    sfText_setCharacterSize(v->text, 75);
    sfText_setColor(v->text, sfRed);
    sfRenderWindow_drawText(v->window, v->text, NULL);
    sfRenderWindow_display(v->window);
}

void paused_game_next_loop(paused_state* ps) {
    paused_game_display_message(ps);
    paused_game_update(ps);
}


void paused_game_update(paused_state* ps) {
    game* g = ps->paused_game;
    int to_game = 0;
    sfEvent *event = malloc(sizeof(sfEvent));
    while (sfRenderWindow_pollEvent(game_get_view_window(g), event)) {
        switch (event->type) {
            case sfEvtClosed:
                sfRenderWindow_close(game_get_view_window(g));
                break;
            case sfEvtKeyPressed:
                if (sfKeyboard_isKeyPressed(sfKeySpace)) {
                    to_game = 1;
                }
                break;
            default:
                break;
        }
    }
    free(event);
    if (to_game) {
        paused_state_to_playing_state(g->state);
    }
}