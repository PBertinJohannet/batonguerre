//
// Created by pierre on 31/08/17.
//

#ifndef STICKWAR_WINDOW_CONF_READER_H
#define STICKWAR_WINDOW_CONF_READER_H

#include "utils.h"
typedef struct window_config window_config;
struct window_config{
    int window_width;
    int window_height;
    int fps;
};
window_config* global_window_config;
struct window_config* get_window_config();


#endif //STICKWAR_WINDOW_CONF_READER_H
