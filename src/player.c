#include "../include/player.h"



struct player_t * init_player(struct location_t position , enum resource_t * rsorc ){
    struct player_t * res = malloc(sizeof(struct player_t));

    res->player_pos = position;
    for(enum resource_t i = 0;i<NB_RESOURCES;i++){
        res->resources[i] = rsorc[i];

    }

    return res;

}


void player_move(struct player_t  *  player , enum direction_t dir){
    switch (dir)
    {
    case NORTH:
        player->player_pos.y += 1;
        break;
    
    case EAST:
        player->player_pos.x += 1;
        break;

    case SOUTH:
        player->player_pos.y -= 1;
        break;

    case WEST:
        player->player_pos.x -= 1;
        break;

    default:
        break;
    }

    
}




