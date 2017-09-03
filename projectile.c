//
// Created by pierre on 24/08/17.
//
#include "projectile.h"
#include "counted_allocations.h"
projectile* projectile_create(int pos, team* team, unsigned int facing){
    projectile* proj = counted_malloc(sizeof(projectile), "creating projectile ");
    proj->team = team;
    proj->pos = pos;
    proj->facing = facing;
    return proj;
}