cmake_minimum_required(VERSION 3.8)
project(stickwar)

set(CMAKE_CXX_STANDARD 11)


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


set(SOURCE_FILES main.c json_frame.h json_frame.c animation.h animation.c view.h drawable_entity.h drawable_entity.c array_list.c array_list.h view.c entity.h entity.c entity_type.h entity_type.c game.h game.c kicker.h entity_factory.h kicker.c controller.h controller.c animation_list.h animation_list.c entity_factory.c game_params.h game_params.c ninja.h ninja.c base.h base.c team.h team.c entity_launcher.h entity_launcher.c texture_list.h texture_list.c dumb_ai.h dumb_ai.c game_state.h game_state.c paused_state.h paused_state.c game_end_state.h game_end_state.c archer.h archer.c projectile.h projectile.c arrow.h arrow.c global.h global.c game_interact.h game_interact.c)
add_executable(stickwar ${SOURCE_FILES})
