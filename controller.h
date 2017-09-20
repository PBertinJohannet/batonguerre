
//
// Created by pierre on 22/08/17.
// This is the battle controller.
// It will process user event at every frame.
//
#ifndef STICKWAR_CONTROLLER_H
#define STICKWAR_CONTROLLER_H

#include "game_state.h"
#include "view.h"
#include "brigade.h"
#include "entity.h"
typedef struct brigade brigade;
typedef struct entity entity;
typedef struct controller controller;
typedef struct battle battle;
/**
 * This is the controller structure, it contains :
 * battle : the battle to controll.
 * selected_brigade : if the user is commanding a brigade, it stores the id of that brigade.
 * commanding_brigade : boolean to say if the user is currently commanding a brigade.
 * selected_unit : pointer to the unit the user is controlling (unused for now).
 */
struct controller {
    battle* battle;
    unsigned int selected_brigade;
    unsigned int commanding_brigade;
    entity* selected_unit;
};
/*
 * Creates the controller struct.
 * @param g : the battle.
 */
controller* controller_init(battle* g);


/*
 * Process all user events.
 * @param c : the controller.
 */
void controller_process_event( controller* c, sfEvent*);


/*
 * Called when the user clicked, will spawn entities or select a brigade to control.
 * @param c : the controller.
 * @param mouse : the coordinates of the mouse.
 */
void controller_process_mouse_click(controller* , sfVector2i mouse);



void controller_destroy(controller* c);
#endif //STICKWAR_CONTROLLER_H