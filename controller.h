
//
// Created by pierre on 22/08/17.
// This is the game controller.
// It will process user event at every frame.
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
/**
 * This is the controller structure, it contains :
 * game : the game to controll.
 * selected_brigade : if the user is commanding a brigade, it stores the id of that brigade.
 * commanding_brigade : boolean to say if the user is currently commanding a brigade.
 * selected_unit : pointer to the unit the user is controlling (unused for now).
 */
struct controller {
    game* game;
    int selected_brigade;
    int commanding_brigade;
    entity* selected_unit;
};
/*
 * Creates the controller struct.
 * @param g : the game.
 */
controller* controller_init(game* g);


/*
 * Process all user events.
 * @param c : the controller.
 */
void controller_process_events( controller* c);


/*
 * Called when the user clicked, will spawn entities or select a brigade to control.
 * @param c : the controller.
 * @param mouse : the coordinates of the mouse.
 */
void controller_process_mouse_click(controller* , sfVector2i mouse);
#endif //STICKWAR_CONTROLLER_H