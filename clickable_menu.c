//
// Created by pierre on 12/09/17.
//
#include "clickable_menu.h"
#include "math.h"
#include "screen_drawer.h"
clickable_menu* clickable_menu_init(){
    clickable_menu* menu = counted_malloc(sizeof(clickable_menu), "creating clickable menu");
    menu->buttons = list_init();
    return menu;
}
void clickable_menu_add_button(clickable_menu* menu, button* b){
    list_add(menu->buttons, b);
}
void clickable_menu_click_event(clickable_menu* menu, sfVector2i mouse){
    mouse.x /= get_window_config()->window_width/1000.0;
    for (unsigned int i = 0; i<menu->buttons->size; i++){
        button* b = list_at(menu->buttons, i);
        if (b->position->x < mouse.x && b->size->x+b->position->x > mouse.x &&
                b->position->y < mouse.y && b->size->y+b->position->y > mouse.y){
            b->callback(b->args);
        }
    }
}
void clickable_menu_draw(clickable_menu* menu, screen_drawer* sd){
    for (unsigned int i = 0; i<menu->buttons->size; i++) {
        button *b = list_at(menu->buttons, i);
        if (b->anim != NULL) {
            sfVector2f pos = {(float) b->position->x-20, (float) b->position->y};
            sfVector2f size = {(float) b->size->x*0.75, (float) b->size->y*1.5};
            screen_drawer_draw_sprite(sd, animation_frame_get_sprite(b->anim, 0), pos, size);
        }
        if (b->text != NULL) {
            sfVector2f pos = {b->position->x, b->position->y};
            screen_drawer_write_text(sd, b->text, sfRed, b->size->y, pos);
        }
    }
}

void clickable_menu_destroy(clickable_menu* menu){
    list_free(menu->buttons, (void(*)(void*))button_destroy);
    counted_free(menu, "destroying clickable menu");
}