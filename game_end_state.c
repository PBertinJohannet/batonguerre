//
// Created by pierre on 23/08/17.
//

#include "game_end_state.h"

void game_end_display_message(game_end_state* g){
    view* v = g->ended_game->view;
    char* text = "Defeat  \n press SPACE to restart";
    if (g->ended_game->player == g->winning_team){
        text =   "Victory \n press SPACE to restart";
    }
    sfText_destroy(v->text);
    v->text = sfText_create();
    sfText_setString(v->text, text);
    sfVector2f position = {WINDOW_HEIGHT/4, WINDOW_WIDTH/4};
    sfText_setPosition(v->text, position);
    sfText_setFont(v->text, v->font);
    sfText_setCharacterSize(v->text, 75);
    sfText_setColor(v->text, sfRed);
    sfRenderWindow_drawText(v->window, v->text, NULL);
}



void game_end_next_loop(game_end_state* ps){
    if (!game_end_update(ps)) {
        for (int i = 0; i < ps->ended_game->entities->size; i++) {
            entity *ent = list_at(ps->ended_game->entities, i);
            if (game_get_team(ps->ended_game, ent->stats->team) != ps->winning_team &&
                ent->drawable->anim->frame == ent->drawable->anim->anim->nb_frames - 2) {
                ent->drawable->anim->frame -= 1;
            }
        }
        view_draw_map(ps->ended_game->view);
        view_draw_launchers(ps->ended_game->view, ps->ended_game->player->spawners);
        game_end_display_message(ps);
        view_draw_entities(ps->ended_game->view, game_get_drawables(ps->ended_game));
    }
}

int game_end_update(game_end_state* es) {
    game* g = es->ended_game;
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
        game_end_state_to_playing_state(es->ended_game->state);
        return 1;
    }
    return 0;
}