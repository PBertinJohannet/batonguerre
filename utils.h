//
// Created by Pierre on 30/08/2017
// This file contains a few functions on strings and stuffs.
//

#ifndef UTILS_H
#define UTILS_H

#include "jansson.h"
#include "string.h"

char* string_concat(char* a, char* b);
json_t* start_json(char *source);
json_t* json_read_elem(json_t* parent, char* elem, char* message, json_type desired);
json_t* json_read_index(json_t* parent, unsigned int index, char* message, json_type desired);
unsigned int json_read_uint(json_t* parent, char* elem);
int json_read_int(json_t* parent, char* elem);
float json_read_float(json_t* parent, char* elem);
const char* json_read_string(json_t* parent, char* elem);
#endif /* UTILS_H */
