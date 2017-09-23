//
// Created by pierre on 16/09/17.
//
#include "campaign_state.h"
#include "parson.h"
#include "utils.h"
campaign_state* campaign_state_new_game(game_state* super, char* game_id){
    campaign_state_copy_base_stats(game_id);
    return campaign_state_load(super, game_id);
}

campaign_state* campaign_state_next_level(game_state* super, char* game_id){
    JSON_Value* val = json_parse_file(campaign_state_get_camp_path(game_id));
    JSON_Object* save = json_value_get_object(val);
    int curr_level = (int)json_object_get_number(save, "level");
    json_object_set_number(save, "level", curr_level+1);
    json_serialize_to_file_pretty(val, campaign_state_get_camp_path(game_id));
    return campaign_state_load(super, game_id);
}

int campaign_state_get_current_level(char* game_id){
    JSON_Object* save = json_value_get_object(json_parse_file(campaign_state_get_camp_path(game_id)));
    return (int)json_object_get_number(save, "level");
}

campaign_state* campaign_state_load(game_state* super, char* game_id){
    campaign_state* campain = counted_malloc(sizeof(campaign_state), "creating campaign state");
    campain->super = super;
    campain->drawer = screen_drawer_init(super->window);
    campain->game_id = game_id;
    campain->menu = campaign_state_menu_init(campain);
    campain->to_main = 0;
    super->current_state->campaign = campain;
    super->process_event = campaign_state_process_event;
    super->update = campaign_state_update;
    super->draw = campaign_state_draw;
    return campain;
}

clickable_menu* campaign_state_menu_init(campaign_state* state){
    clickable_menu* menu = clickable_menu_init();
    //JSON_Object* camp_json = json_value_get_object(json_parse_file((campaign_state_get_camp_path(game_id)));
    //int a = (int)json_object_get_number(camp_json, "level");
    clickable_menu_add_button(menu, button_inline_init((void(*)(void*))campaign_state_switch_to_battle, state, 400, 400, 30, "next level", NULL));
    return menu;
}

char* campaign_state_get_camp_path(char* game_id){
    char* camp = counted_malloc(sizeof(char)*(strlen("confs/saves//campaign.json")+strlen(game_id)+1), "creating new campaign path for camp");
    sprintf(camp, "confs/saves/%s/campaign.json", game_id);
    return camp;
}
char* campaign_state_get_army_path(char* game_id){
    char* army = counted_malloc(sizeof(char)*(strlen("confs/saves//army.json")+strlen(game_id)+1), "creating new campaign path for camp");
    sprintf(army, "confs/saves/%s/army.json", game_id);
    return army;
}

void campaign_state_copy_base_stats(char* game_id){
    printf("copy base stats wllh \n");
    char* camp = campaign_state_get_camp_path(game_id);
    char* army = campaign_state_get_army_path(game_id);
    copy_json_to("confs/base/army.json", army);
    copy_json_to("confs/base/campaign.json", camp);
    counted_free(army, "freeing army campaign path");
    counted_free(camp, "freeing camp campaign path");
}


void campaign_state_draw(game_state_union* state){
    campaign_state* campaign = state->campaign;
    screen_drawer_clear(campaign->drawer);
    clickable_menu_draw(campaign->menu, campaign->drawer);
}
__attribute_const__ void campaign_state_update(game_state_union* ps){
    if (ps->campaign->to_main){
        campaign_state_to_battle(ps->campaign);
    }
}
void campaign_state_process_event(game_state_union* state, sfEvent* event){
    campaign_state* campaign = state->campaign;
    switch (event->type) {
        case sfEvtClosed:
            sfRenderWindow_close(campaign->super->window);
            break;
        case sfEvtMouseButtonPressed:
            clickable_menu_click_event(campaign->menu, sfMouse_getPositionRenderWindow(campaign->super->window));
            break;
        default:
            break;
    }
    if (campaign->to_main){
        campaign_state_to_battle(campaign);
    }
}
void campaign_state_switch_to_battle(campaign_state* camp){
    camp->to_main = 1;
}
void campaign_state_to_battle(campaign_state* campaign){
    game_state* state = campaign->super;
    //JSON_Object* camp_json = json_value_get_object(json_parse_file((campaign_state_get_camp_path(game_id)));
    state->current_state->battle = battle_state_init_from_level(state,
                                                                int_to_str(campaign_state_get_current_level(campaign->game_id)),
                                                                campaign->game_id);
    state->draw = battle_state_draw;
    state->process_event = battle_state_process_event;
    state->update = battle_state_update;
    screen_drawer_destroy(campaign->drawer);
    clickable_menu_destroy(campaign->menu);
    counted_free(campaign, "freeing campaign");
}