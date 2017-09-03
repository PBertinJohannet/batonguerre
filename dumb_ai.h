//
// Created by pierre on 23/08/17.
// This is the basic, stupid AI, will put all units in defense and attack if you do.
//

#ifndef STICKWAR_DUMB_AI_H
#define STICKWAR_DUMB_AI_H

#include "game.h"
#include "team.h"
#include "entity_launcher.h"
#include "game_interact.h"
#include "ai.h"
typedef struct ai ai;
typedef struct team team;
typedef struct dumb_ai dumb_ai;

/**
 * This is the AI.
 * the last_ass says if the ai already ordered to assault.
 * team is the ennemy team.
 * target_id is not used for now but will contain the targeted zone to fight for.
 */
struct dumb_ai{
    team* team;
    int last_ass;
    unsigned int target_id;
};

/**
 * Creates the dumb ai.
 * @param t : the team controlled by the ai.
 */
dumb_ai* dumb_ai_init(team* t);


/**
 * Choose if the ai must attack or stay and return the result.
 * @param ai : the ai.
 * @param entities : the list of ennemy entities.
 */
int choose_mode(dumb_ai* ai, list* entities);


/**
 * Play, creates a random unit and decides to attack, advance or retreat.
 * @param dai : the ai.
 * @param g : the game.
 */
void dumb_ai_play(ai* dai, game* g);


/**
 * Destroys the AI.
 * @param dai : the ai.
 */
void dumb_ai_destroy(dumb_ai* dai);
#endif //STICKWAR_DUMB_AI_H
