//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_CONTROLLER_H
#define STICKWAR_CONTROLLER_H

#include "game.h"
#include "view.h"
#include "brigade.h"
#include "entity.h"
typedef struct brigade brigade;
typedef struct entity entity;
typedef struct controller controller;
typedef struct game game;
struct controller {
    game* game;
    int selected_brigade;
    int commanding_brigade;
    entity* selected_unit;
};
controller* controller_init(game* g);
void controller_process_events( controller* c);

void controller_process_mouse_click(controller* , sfVector2i mouse);
#endif //STICKWAR_CONTROLLER_H
