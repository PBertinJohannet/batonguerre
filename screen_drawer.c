//
// Created by pierre on 14/09/17.
//

#include "screen_drawer.h"

screen_drawer* screen_drawer_init(sfRenderWindow* window){
    screen_drawer* s = counted_malloc(sizeof(screen_drawer), "screen_drawer create");
    s->window = window;
    s->font = sfFont_createFromFile("fonts/OpenSans-Bold.ttf");
    s->texts = list_init();
    s->sprites = list_init();
    return s;
}
void screen_drawer_draw_sprite(screen_drawer* v, sfSprite* sprite, sfVector2f position, sfVector2f size){
    list_add(v->sprites, sprite);
    sfFloatRect bounds = sfSprite_getGlobalBounds(sprite);
    sfVector2f scale = {size.x/bounds.height, size.y/bounds.height};
    sfSprite_setScale(sprite,scale);
    position.x *=get_window_config()->window_width/1000.0;
    position.y *=get_window_config()->window_height/1000.0;
    sfSprite_setPosition(sprite, position);
    sfRenderWindow_drawSprite(v->window, sprite, NULL);
}

void screen_drawer_sprite_center(sfSprite* sprite){
    sfFloatRect bounds = sfSprite_getGlobalBounds(sprite);
    sfVector2f origin = {bounds.width/2, bounds.height};
    sfSprite_setOrigin(sprite, origin);

}

void screen_drawer_write_text(screen_drawer* sc, char* to_write, sfColor color, unsigned int size, sfVector2f position) {
    sfText* text = sfText_counted_malloc("create text in screen drawer");
    list_add(sc->texts, text);
    sfText_setString(text, to_write);
    sfText_setFont(text, sc->font);
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, color);
    position.x *=get_window_config()->window_width/1000.0;
    position.y *=get_window_config()->window_height/1000.0;
    sfText_setPosition(text, position);
    sfRenderWindow_drawText(sc->window, text, NULL);
}

void screen_drawer_clear(screen_drawer* sc){
    for (unsigned int i = 0; i<sc->texts->size; i++) {
        sfText* text = list_at(sc->texts, i);
        sfText_counted_free(text, "clearing list screen drawer");
    }
    for (unsigned int i = 0; i<sc->sprites->size; i++) {
        sfSprite* sprite = list_at(sc->sprites, i);
        sfSprite_counted_free(sprite, "clearing list screen drawer");
    }
    list_clear_no_free(sc->texts);
    list_clear_no_free(sc->sprites);
}

void screen_drawer_destroy(screen_drawer* v){
    screen_drawer_clear(v);
    list_destroy(v->texts);
    sfFont_destroy(v->font);
    counted_free(v, "freeing screen_drawer");
}