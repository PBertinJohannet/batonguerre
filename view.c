//
// Created by pierre on 21/08/17.
//
#include <SFML/Graphics/Rect.h>
#include "view.h"
#include "entity_launcher.h"
#include "global.h"
#include "brigade.h"
#include "level_reader.h"
view* view_init(sfRenderWindow* window, battle_config* battle_conf){
    view* v = malloc(sizeof(view));
    v->window = window;
    v->battle_config = battle_conf;
    sfRenderWindow_setFramerateLimit(v->window, FPS);
    v->font = sfFont_createFromFile("fonts/OpenSans-Bold.ttf");
    v->text = sfText_create();
    v->camera_position = 50;
    return v;
}
void view_play_music(view* v, char* name){
    sfMusic* music = sfMusic_createFromFile(name);
    sfMusic_play(music);
}
void view_draw_sprite(view* v, sfSprite* sprite, sfVector2f position, sfVector2f size, int rel){
    if (rel){
        position.x -= v->camera_position;
        view_sprite_center(sprite);
    }
    sfFloatRect bounds = sfSprite_getGlobalBounds(sprite);
    sfVector2f scale = {size.x/bounds.height, size.y/bounds.height};
    sfSprite_setScale(sprite,scale);
    position.x *=WINDOW_WIDTH/1000.0;
    sfSprite_setPosition(sprite, position);
    sfRenderWindow_drawSprite(v->window, sprite, NULL);
}
void view_draw_launchers(view* v, list* launchers){
    for (int i = 0;i<launchers->size;i++){
        entity_launcher* launcher = ((brigade*)list_at(launchers, i))->launcher;
        sfSprite* icon = entity_launcher_get_icon(launcher);
        sfVector2f position = {(i)*50, 50};
        sfVector2f scale = {100,100};
        view_draw_sprite(v,icon,position,scale,0);
    }
}


void view_draw_cursor(view* v, int commanding){
    if (commanding){
        sfRenderWindow_setMouseCursorVisible(v->window,0);
        sfSprite* image = sfSprite_create();
        sfSprite_setTexture(image, get_textures()->flag,0);
        sfVector2f new_scale = {200.0,200.0};
        sfVector2i mouse = sfMouse_getPositionRenderWindow(v->window);
        sfVector2f position = {mouse.x*1000/WINDOW_WIDTH, mouse.y};
        sfFloatRect bounds = sfSprite_getGlobalBounds(image);
        sfVector2f origin = {bounds.width/2, bounds.height/2};
        sfSprite_setOrigin(image, origin);
        view_draw_sprite(v,image,position,new_scale,0);
    } else {
        sfRenderWindow_setMouseCursorVisible(v->window, 1);
    }
}

void view_draw_entity(view* v, drawable_entity* dw){
    sfSprite* to_draw = animation_frame_next(dw->anim, *dw->facing);
    sfVector2f pos = {*dw->pos, v->ground_position};
    sfVector2f scale = {dw->size*100.f, dw->size*100.f};
    view_draw_sprite(v,to_draw,pos,scale,1);
}

void view_draw_map(view* v){
    sfRenderWindow_clear(v->window, sfBlack);
    view_draw_background(v);
    view_draw_assault(v);
    view_draw_retreat(v);
}

void view_draw_background(view* v){
    sfSprite* image = sfSprite_create();
    sfSprite_setTexture(image, get_textures()->background,0);
    sfVector2f new_scale = {v->battle_config->map_size/1.75,WINDOW_HEIGHT};
    sfVector2f position = {0 - v->camera_position, 0};
    view_draw_sprite(v,image,position,new_scale,0);
}
void view_draw_assault(view* v){
    sfSprite* image = sfSprite_create();
    sfSprite_setTexture(image, get_textures()->assault,0);
    sfVector2f new_scale = {200.0,200.0};
    sfVector2f position = {200,-50};
    view_draw_sprite(v,image,position,new_scale,0);
}
void view_draw_retreat(view* v){
    sfSprite* image = sfSprite_create();
    sfSprite_setTexture(image, get_textures()->retreat,0);
    sfVector2f new_scale = {200.0,200.0};
    sfVector2f position = {100,-50};
    view_draw_sprite(v,image,position,new_scale,0);
}


void view_sprite_center(sfSprite* sprite){
    sfFloatRect bounds = sfSprite_getGlobalBounds(sprite);
    sfVector2f origin = {bounds.width/2, bounds.height};
    sfSprite_setOrigin(sprite, origin);

}

void view_draw_entities(view* v, list* entities){
    for (int i =0;i<entities->size;i++){
        drawable_entity* dw = (drawable_entity*)list_at(entities,i);
        view_draw_entity(v,dw);
    }
    sfRenderWindow_display(v->window);
}

void view_draw_gold(view* v, int gold){
    sfText_destroy(v->text);
    v->text = sfText_create();
    char nb[12];
    sprintf(nb, "Gold : %d", gold);
    sfText_setString(v->text, nb);
    sfText_setFont(v->text, v->font);
    sfText_setCharacterSize(v->text, 20);
    sfText_setColor(v->text, sfRed);
    sfRenderWindow_drawText(v->window, v->text,NULL);
}

void view_move_right(view* v){
    if (v->camera_position < v->battle_config->map_size-900-50){
        v->camera_position+=30;
    }
}
void view_move_left(view* v){
    if (v->camera_position >30){
        v->camera_position-=30;
    }
}



void game_over_screen(view* v) {
    sfRenderWindow_clear(v->window, sfBlack);
    sfText_destroy(v->text);
    v->text = sfText_create();
    sfText_setString(v->text, " DEFEAT ");
    sfText_setFont(v->text, v->font);
    sfText_setCharacterSize(v->text, 50);
    sfText_setColor(v->text, sfRed);
    sfRenderWindow_drawText(v->window, v->text, NULL);
    sfRenderWindow_display(v->window);
}

void win_screen(view* v) {
    sfRenderWindow_clear(v->window, sfBlack);
    sfText_destroy(v->text);
    v->text = sfText_create();
    sfText_setString(v->text, " VICTORY ");
    sfText_setFont(v->text, v->font);
    sfText_setCharacterSize(v->text, 50);
    sfText_setColor(v->text, sfRed);
    sfRenderWindow_drawText(v->window, v->text, NULL);
    sfRenderWindow_display(v->window);
}



void view_destroy(view* v){
    sfText_destroy(v->text);
    sfFont_destroy(v->font);
    free(v);
}