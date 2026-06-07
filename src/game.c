#include "../include/game.h"

struct game_t *game_create(struct map_t map, struct player_t *player, struct location_t exit_location, struct location_t start_location) {
    struct game_t *game = malloc(sizeof(struct game_t));
    game->map = map;
    game->player = player;
    game->exit_location = exit_location;
    game->start_location = start_location;
    return game;
}

void free_game(struct game_t *game) {
    free(game->player);
    for (int i = 0; i < game->map.height; i++) {
        free(game->map.grid[i]);
    }
    free(game->map.grid);
    free(game);
}

void player_gain_resource(struct game_t *game, enum ground_t resource) {
    //si on est sur une case flower on gagne +2 en MOVE , sur SAND +2 en WATER et on remplace le ground par du graass
    if (resource == FLOWER) {
        game->player->resources[MOVE] += 2;
        game->map.grid[game->player->player_pos.y][game->player->player_pos.x] = GRASS;
    } else if (resource == SAND) {
        game->player->resources[WATER] += 2;
        game->map.grid[game->player->player_pos.y][game->player->player_pos.x] = GRASS;
    }

}


void print_game(struct game_t *game) {
    printf("Player position: (%d, %d)\n", game->player->player_pos.x, game->player->player_pos.y);
    printf("Player resources: MOVE=%d, WATER=%d, TIME=%d\n", game->player->resources[MOVE], game->player->resources[WATER], game->player->resources[TIME]);
    //on affiche la map avec un P pour le plawer et premiere lettre du ground pour les cases
    for (int i = 0; i < game->map.height; i++) {
        for (int j = 0; j < game->map.width; j++) {
            if (game->player->player_pos.x == j && game->player->player_pos.y == i) {
                printf("P ");
            } else {
                switch (game->map.grid[i][j]) {
                    case GRASS:
                        printf("G ");
                        break;        
                    case FLOWER:
                        printf("F ");
                        break;
                    case FIRE:
                        printf("R ");
                        break;
                    case SAND:
                        printf("S ");
                        break;
                    case WALL:
                        printf("W ");
                        break;
                    default:
                        printf("? ");
                        break;

}
            }
        }
        printf("\n");
    }
}