//
// Created by pierre on 22/08/17.
//

#include "animation_list.h"
#include "counted_allocations.h"

animation_list* animation_list_load(){
    animation_list* anim = counted_malloc(sizeof(animation_list), "animation list load");
    anim->stick_walk = animation_init("walk_stick");
    anim->stick_kick = animation_init("kick_stick");
    anim->stick_kick_death = animation_init("kick_death");
    anim->stick_walk_death = animation_init("walk_death");
    anim->ninja_walk = animation_init("ninja_walk");
    anim->ninja_strike = animation_init("ninja_strike"); // err here !
    anim->ninja_death = animation_init("ninja_death");
    anim->ninja_icon = animation_init("ninja_icon");
    anim->kicker_icon = animation_init("kicker_icon");
    anim->kicker_punch = animation_init("kicker_punch");
    anim->ninja_slash = animation_init("ninja_slash");
    anim->archer_critical_hit = animation_init ("archer_critical_hit");
    anim->archer_death = animation_init ("archer_death");
    anim->archer_hit = animation_init ("archer_hit");
    anim->archer_walk = animation_init("archer_walk");
    anim->archer_short_hit = animation_init("archer_short_hit");
    anim->arrow = animation_init("arrow");
    anim->ninja_jump = animation_init("ninja_jump");
    anim->gold_heap = animation_init("gold_heap");
    anim->mining = animation_init("mining");
    anim->mineworker_walk = animation_init("mineworker_walk");
    anim->button = animation_init("button");
    return anim;
}




void animation_list_destroy(animation_list* anims){
    animation_destroy(anims->stick_walk);
    animation_destroy(anims->stick_kick);
    animation_destroy(anims->stick_kick_death);
    animation_destroy(anims->stick_walk_death);
    animation_destroy(anims->ninja_walk);
    animation_destroy(anims->ninja_strike);
    animation_destroy(anims->ninja_death);
    animation_destroy(anims->ninja_icon);
    animation_destroy(anims->kicker_icon);
    animation_destroy(anims->kicker_punch);
    animation_destroy(anims->ninja_slash);
    animation_destroy(anims->archer_critical_hit);
    animation_destroy(anims->archer_death);
    animation_destroy(anims->archer_hit);
    animation_destroy(anims->archer_walk);
    animation_destroy(anims->archer_short_hit);
    animation_destroy(anims->arrow);
    animation_destroy(anims->ninja_jump);
    animation_destroy(anims->gold_heap);
    animation_destroy(anims->mining);
    animation_destroy(anims->mineworker_walk);
    animation_destroy(anims->button);
    counted_free(anims, "remove animation list");
}