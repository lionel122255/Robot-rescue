#ifndef GAME_H
#define GAME_H



#include "map.h"
#include "player.h"

struct game_t {
    struct map_t map;
    struct player_t * player;
    struct location_t exit_location;
    struct location_t start_location;
};


struct game_t *game_create(struct map_t map, struct player_t *player, struct location_t exit_location, struct location_t start_location);

void free_game(struct game_t *game);

void player_gain_resource(struct game_t *game, enum ground_t resource);

void print_game(struct game_t *game);














#endif