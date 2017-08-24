//
// Created by pierre on 24/08/17.
//
#include "arrow.h"
#include "entity.h"
projectile* arrow_create(int pos, int team, int facing, int damage){
    arrow* arrow = malloc(sizeof(arrow));
    projectile* proj = projectile_create(pos, team, facing);
    arrow->damage = damage;
    arrow->lifetime = ARCHER_LONG_RANGE*FPS/ARROW_SPEED;
    arrow->parent = proj;
    proj->drawable = drawable_entity_init(animation_frame_init(animation_init("arrow")),&proj->pos, &proj->facing,ARROW_SIZE);
    proj->play = arrow_projectile_play;
    proj->self = arrow;
    proj->facing = facing;
    proj->destroy = arrow_projectile_destroy;
    return proj;
}


int arrow_projectile_play(void* proj, list* entities){
    projectile* pj = proj;
    arrow* p_arr = pj->self;
    for (int i = 0;i<entities->size;i++){
        entity* ent = list_at(entities,i);
        if (ent->team != pj->team
                && ent->hp>0
                && abs(ent->pos - pj->pos) < 20){
                ent->hp-= p_arr->damage;
                return 1;
        }
    }
    pj->pos-=(2*pj->facing-1)*ARROW_SPEED/FPS;
    p_arr->lifetime--;
    if (p_arr->lifetime<1){
        return 1;
    }
    return 0;
}

int arrow_projectile_destroy(projectile* proj){
    projectile* pj = proj;
    arrow* p_arr = pj->self;
    drawable_entity_destroy(pj->drawable);
    free(p_arr);
    free(proj);
    return 0;
}