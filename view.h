//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_DRAWER_H
#define STICKWAR_DRAWER_H

#include <SFML/Graphics.h>
#include "drawable_entity.h"
#include "array_list.h"
#include "texture_list.h"
#include "level_reader.h"
#include "screen_drawer.h"
typedef struct battle_config battle_config;
typedef struct view view;
struct view{
    sfRenderWindow* window;
    screen_drawer* drawer;
    unsigned int camera_position;
    battle_config* battle_config;
    int last_fps;
};
view* view_init(sfRenderWindow*, battle_config* battle_config);
void view_draw_cursor(view* v, unsigned int commanding);
void view_draw_sprite(view* v, sfSprite* sprite, sfVector2f position, sfVector2f size, int rel);
void view_draw_launchers(view* v, list* launchers);
void view_draw_entity(view* v, drawable_entity* dw);
void view_draw_map(view* v);
void view_draw_background(view* v);
void view_draw_assault(view* v);
void view_draw_retreat(view* v);
void view_draw_entities(view* v, list* entities);
void view_move_right(view* v);
void view_move_left(view* v);
void view_draw_gold(view* v, int gold);
void view_destroy(view* v);
void view_draw_perf(view* v, int , int);
void view_draw_info(view* v, char* title, int to_draw, int x, int y);
#endif //STICKWAR_DRAWER_H
