//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_CONTROLLER_H
#define STICKWAR_CONTROLLER_H

#include "game.h"
#include "view.h"
typedef struct controller controller;
typedef struct game game;
void controller_process_events( game* g);

void controller_process_mouse_click(game* g, sfVector2i mouse);
#endif //STICKWAR_CONTROLLER_H
