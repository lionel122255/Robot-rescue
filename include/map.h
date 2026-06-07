

#ifndef MAP_H
#define MAP_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"


enum ground_t {
    GRASS,
    FLOWER,
    FIRE,
    SAND,
    WALL
};

struct map_t {
    enum ground_t ** grid;
    int width;
    int height;

};

struct map_t load_map(const char * filename);


#endif