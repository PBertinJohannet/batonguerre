//
// Created by Pierre on 30/08/2017
// This file contains a few functions on strings and stuffs.
//

#ifndef UTILS_H
#define UTILS_H

char* string_concat(char* a, char* b);


json_t* start_json(char* source);
json_t* read_elem(json_t* parent, char* elem, char* message, json_type desired);
json_t* read_index(json_t* parent, int index, char* message, json_type desired);
#endif /* UTILS_H */
