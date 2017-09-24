//
// Created by pierre on 21/08/17.
//
#include <SFML/Graphics/Rect.h>
#include "view.h"
#include "entity_launcher.h"
#include "global.h"
#include "brigade.h"
#include "level_reader.h"
#include "window_conf_reader.h"
#include "counted_allocations.h"
view* view_init(sfRenderWindow* window, battle_config* battle_conf){
    view* v = counted_malloc(sizeof(view), "view create");
    v->window = window;
    v->battle_config = battle_conf;
    v->drawer = screen_drawer_init(window);
    v->camera_position = 50;
    v->last_fps = -1;
    return v;
}
void view_draw_sprite(view* v, sfSprite* sprite, sfVector2f position, sfVector2f size, int rel){
    if (rel){
        position.x -= v->camera_position;
        screen_drawer_sprite_center(sprite);
    }
    screen_drawer_draw_sprite(v->drawer, sprite, position, size);
}
void view_draw_launchers(view* v, list* launchers){
    for (unsigned int i = 0;i<launchers->size;i++){
        entity_launcher* launcher = ((brigade*)list_at(launchers, i))->launcher;
        sfSprite* icon = entity_launcher_get_icon(launcher);
        sfVector2f position = {(i)*50, 50};
        sfVector2f scale = {100,100};
        view_draw_sprite(v,icon,position,scale,0);
    }
}


void view_draw_cursor(view* v, unsigned int commanding){
    if (commanding){
        sfRenderWindow_setMouseCursorVisible(v->window,0);
        sfSprite* image = sfSprite_counted_malloc("creating sprite in view draw cursor");
        sfSprite_setTexture(image, get_textures()->flag,0);
        sfVector2f new_scale = {200.0,200.0};
        sfVector2i mouse = sfMouse_getPositionRenderWindow(v->window);
        sfVector2f position = {(unsigned int)(mouse.x)*1000/get_window_config()->window_width, mouse.y};
        sfFloatRect bounds = sfSprite_getGlobalBounds(image);
        sfVector2f origin = {bounds.width/2, bounds.height/2};
        sfSprite_setOrigin(image, origin);
        view_draw_sprite(v,image,position,new_scale,0);
    } else {
        sfRenderWindow_setMouseCursorVisible(v->window, 1);
    }
}

void view_draw_entity(view* v, drawable_entity* dw){
    sfSprite* to_draw = animation_frame_get_sprite(dw->anim, *dw->facing);
    sfVector2f pos = {*dw->pos, v->battle_config->ground_pos};
    sfVector2f scale = {dw->size*100.f, dw->size*100.f};
    view_draw_sprite(v,to_draw,pos,scale,1);
}

void view_draw_map(view* v){
    view_draw_background(v);
    view_draw_assault(v);
    view_draw_retreat(v);
}

void view_draw_background(view* v){
    sfSprite* image = sfSprite_counted_malloc("creating sprite for background");
    sfSprite_setTexture(image, get_textures()->background,0);
    sfVector2f new_scale = {((float)v->battle_config->map_size)/1.75f,(float)get_window_config()->window_height};
    sfVector2f position = {0.f - (float)v->camera_position, 0.f};
    view_draw_sprite(v,image,position,new_scale,0);
}
void view_draw_assault(view* v){
    sfSprite* image = sfSprite_counted_malloc("creating sprite for assault");
    sfSprite_setTexture(image, get_textures()->assault,0);
    sfVector2f new_scale = {200.0,200.0};
    sfVector2f position = {200,-50};
    view_draw_sprite(v,image,position,new_scale,0);
}
void view_draw_retreat(view* v){
    sfSprite* image = sfSprite_counted_malloc("creating sprite for retreat");
    sfSprite_setTexture(image, get_textures()->retreat,0);
    sfVector2f new_scale = {200.0,200.0};
    sfVector2f position = {100,-50};
    view_draw_sprite(v,image,position,new_scale,0);
}


void view_draw_entities(view* v, list* entities){
    for (unsigned int i =0;i<entities->size;i++){
        drawable_entity* dw = (drawable_entity*)list_at(entities,i);
        view_draw_entity(v,dw);
    }
}

void view_draw_gold(view* v, int gold){
    view_draw_info(v, "Gold : %d", gold, 0,0);
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


void view_destroy(view* v){
    screen_drawer_destroy(v->drawer);
    battle_config_destroy(v->battle_config);
    counted_free(v, "freeing view");
}
void view_draw_info(view* v, char* title, int to_draw, int x, int y){
    char nb[200];
    sprintf(nb, title, to_draw);
    sfVector2f position = {x,y};
    screen_drawer_write_text(v->drawer, nb, sfRed, 20, position);
}
void view_draw_perf(view* v, int entities, int objects){
    // fps
    int act_fps = (int)(1.f/get_elapsed_sec());
    if (v->last_fps==-1){
        v->last_fps = act_fps;
    }
    v->last_fps = (v->last_fps*act_fps+act_fps)/(act_fps+1);
    view_draw_info(v, "fps : %d", v->last_fps, 920, 0);
    view_draw_info(v, "entities : %d", entities, 920, 50);
    view_draw_info(v, "objects : %d", objects, 920, 100);
}