

#ifndef PLAYER_H
#define PLAYER_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_RESOURCES 3

enum direction_t{
    NORTH,
    EAST,
    SOUTH,
    WEST,
    MAX_DIRS
};

/*structure to manage the locations in the game*/

struct location_t {
    int x;
    int y ;
};

enum resource_t {
    MOVE,
    WATER,
    TIME,
};




struct player_t {
    struct location_t player_pos;
    enum resource_t resources [NB_RESOURCES] ;
};



struct player_t * init_player(struct location_t position , enum resource_t * rsorc );


void player_move(struct player_t  *  player , enum direction_t dir);








#endif