cmake_minimum_required(VERSION 3.8)
project(stickwar)

set(CMAKE_CXX_STANDARD 11)


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


set(SOURCE_FILES main.c json_frame.h json_frame.c animation.h animation.c view.h drawable_entity.h drawable_entity.c array_list.c array_list.h view.c entity.h entity.c entity_behaviour.h entity_behaviour.c game_state.h battle.c kicker.h entity_factory.h kicker.c controller.h controller.c animation_list.h animation_list.c entity_factory.c battle_params.h battle_params.c ninja.h ninja.c base.h base.c team.h team.c entity_launcher.h entity_launcher.c texture_list.h texture_list.c dumb_ai.h dumb_ai.c game_state.h game_state.c paused_state.h paused_state.c battle.h battle.c archer.h archer.c object.h object.c arrow.h arrow.c global.h global.c battle_interact.h battle_interact.c command.h brigade.h brigade.c command.c loader.h level_reader.c ai.h ai.c utils.c window_conf_reader.h window_conf_reader.c brigade_reader.h brigade_reader.c brigade_reader.c counted_allocations.h counted_allocations.c battle.h battle.c gold_heap.h gold_heap.c mineworker.h mineworker.c clickable_menu.h button.h main_menu_state.h main_menu_state.c button.c clickable_menu.c screen_drawer.h screen_drawer.c campaign_state.h campaign_state.c)
add_executable(stickwar ${SOURCE_FILES})
