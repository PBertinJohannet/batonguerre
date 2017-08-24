//
// Created by pierre on 24/08/17.
//
#include "projectile.h"

projectile* projectile_create(int pos, int team, int facing){
    projectile* proj = malloc(sizeof(projectile));
    proj->team = team;
    proj->pos = pos;
    proj->facing = facing;
    return proj;
}