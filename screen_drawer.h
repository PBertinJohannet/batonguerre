//
// Created by pierre on 14/09/17.
//

#ifndef STICKWAR_SCREEN_DRAWER_H
#define STICKWAR_SCREEN_DRAWER_H

typedef struct screen_drawer screen_drawer;
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "array_list.h"
#include "counted_allocations.h"
#include "window_conf_reader.h"
struct screen_drawer {
    sfRenderWindow* window;
    sfFont* font;
    list* texts;
    list* sprites;
};
screen_drawer* screen_drawer_init(sfRenderWindow* window);
void screen_drawer_play_music( screen_drawer* v, char* name);
void screen_drawer_draw_sprite(screen_drawer* v, sfSprite* sprite, sfVector2f position, sfVector2f size);
void screen_drawer_sprite_center(sfSprite* sprite);
void screen_drawer_write_text(screen_drawer* sc, char* to_write, sfColor color, unsigned int size, sfVector2f position);
void screen_drawer_clear(screen_drawer* sc);
void screen_drawer_destroy(screen_drawer* v);
#endif //STICKWAR_SCREEN_DRAWER_H
