//
// Created by pierre on 11/09/17.
//

#ifndef STICKWAR_CLICKABLE_MENU_H
#define STICKWAR_CLICKABLE_MENU_H

#include "button.h"
#include "view.h"
typedef struct view view;
typedef struct clickable_menu clickable_menu;
struct clickable_menu {
    list* buttons;
};

clickable_menu* clickable_menu_init(void);
void clickable_menu_add_button(clickable_menu* menu, button* b);
void clickable_menu_click_event(clickable_menu* menu, sfVector2i mouse);
void clickable_menu_draw(clickable_menu* menu, sfVector2i mouse, view* v);

#endif //STICKWAR_CLICKABLE_MENU_H
