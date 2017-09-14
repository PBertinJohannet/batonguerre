//
// Created by pierre on 12/09/17.
//
#include "clickable_menu.h"
#include "math.h"
clickable_menu* clickable_menu_init(){
    clickable_menu* menu = counted_malloc(sizeof(clickable_menu), "creating clickable menu");
    menu->buttons = list_create();
    return menu;
}
void clickable_menu_add_button(clickable_menu* menu, button* b){
    list_add(menu->buttons, b);
}
void clickable_menu_click_event(clickable_menu* menu, sfVector2i mouse){
    for (unsigned int i = 0; i<menu->buttons->size; i++){
        button* b = list_at(menu->buttons, i);
        if (b->position->x < mouse.x && b->size->x+b->position->x > mouse.x &&
                b->position->y < mouse.y && b->size->y+b->position->x > mouse.y){
            printf("clicked on button at %d, %d\n", b->position->x, b->position->y);
            b->callback(b->args);
        }
    }
}
void clickable_menu_draw(clickable_menu* menu, sfVector2i mouse, view* v){
    for (unsigned int i = 0; i<menu->buttons->size; i++){
        button* b = list_at(menu->buttons, i);
        if (b->position->x < mouse.x && b->size->x+b->position->x > mouse.x &&
            b->position->y < mouse.y && b->size->y+b->position->x > mouse.y){
            sfVector2f pos = {(float)b->position->x, (float)b->position->y};
            sfVector2f size = {(float)b->size->x, (float)b->size->y};
            view_draw_sprite(v, animation_frame_next(b->anim, 0), pos, size, 0);
        }
    }
}