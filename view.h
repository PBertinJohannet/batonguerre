//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_DRAWER_H
#define STICKWAR_DRAWER_H

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "drawable_entity.h"
#include "array_list.h"
#include "game_params.h"
#include "texture_list.h"
typedef struct view view;
struct view{
    sfRenderWindow* window;
    sfFont* font;
    sfText* text;
    int camera_position;
};
view* view_init(sfRenderWindow*);
void view_play_music(view* v, char* name);
void view_draw_cursor(view* v, int commanding);
void view_draw_sprite(view* v, sfSprite* sprite, sfVector2f position, sfVector2f size, int rel);
void view_draw_launchers(view* v, list* launchers);
void view_sprite_center(sfSprite* sprite);
void view_draw_entity(view* v, drawable_entity* dw);
void view_draw_map(view* v);
void view_draw_background(view* v);
void view_draw_assault(view* v);
void view_draw_retreat(view* v);
void view_draw_entities(view* v, list* entities);
void view_move_right(view* v);
void view_move_left(view* v);
void view_draw_gold(view* v, int gold);
void game_over_screen(view* v);
void win_screen(view* v);
void view_destroy(view* v);
#endif //STICKWAR_DRAWER_H
