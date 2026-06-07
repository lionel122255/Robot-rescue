
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/map.h"
#include "../include/player.h"
#include "../include/game.h"

/* ===================== COLORS ===================== */

#define GREEN  "\033[0;32m"
#define RED    "\033[0;31m"
#define BLUE   "\033[0;34m"
#define YELLOW "\033[0;33m"
#define RESET  "\033[0m"

/* ===================== DISPLAY ===================== */

static void print_section(const char *title) {
    printf(
        BLUE
        "\n====================================\n"
        "%s\n"
        "====================================\n"
        RESET,
        title
    );
}

static void print_success(const char *test_name) {
    printf(GREEN "[PASS] " RESET "%s\n", test_name);
}

/* ===================== TESTS ===================== */

static void test_load_map(void) {

    struct map_t map = load_map("./map/level1.txt");

    assert(map.width > 0);
    assert(map.height > 0);
    assert(map.grid != NULL);

    print_success("load_map");

    for (int i = 0; i < map.height; i++) {
        free(map.grid[i]);
    }

    free(map.grid);
}

static void test_init_player(void) {

    struct location_t pos = {1, 1};

    enum resource_t resources[NB_RESOURCES];

    resources[MOVE] = 10;
    resources[WATER] = 5;
    resources[TIME] = 20;

    struct player_t *player = init_player(pos, resources);

    assert(player != NULL);

    assert(player->player_pos.x == 1);
    assert(player->player_pos.y == 1);

    assert(player->resources[MOVE] == 10);
    assert(player->resources[WATER] == 5);
    assert(player->resources[TIME] == 20);

    print_success("init_player");

    free(player);
}

static void test_player_move(void) {

    struct location_t pos = {5, 5};

    enum resource_t resources[NB_RESOURCES] = {0};

    struct player_t *player = init_player(pos, resources);

    player_move(player, NORTH);

    assert(player->player_pos.x == 5);
    assert(player->player_pos.y == 4);

    player_move(player, SOUTH);

    assert(player->player_pos.x == 5);
    assert(player->player_pos.y == 5);

    player_move(player, EAST);

    assert(player->player_pos.x == 6);
    assert(player->player_pos.y == 5);

    player_move(player, WEST);

    assert(player->player_pos.x == 5);
    assert(player->player_pos.y == 5);

    print_success("player_move");

    free(player);
}

static void test_game_create(void) {

    struct map_t map = load_map("./map/level1.txt");

    struct location_t start = {1, 1};
    struct location_t exit = {map.width - 2, map.height - 2};

    enum resource_t resources[NB_RESOURCES];

    resources[MOVE] = 10;
    resources[WATER] = 10;
    resources[TIME] = 10;

    struct player_t *player = init_player(start, resources);

    struct game_t *game =
        game_create(map, player, exit, start);

    assert(game != NULL);

    assert(game->player == player);

    assert(game->start_location.x == start.x);
    assert(game->start_location.y == start.y);

    assert(game->exit_location.x == exit.x);
    assert(game->exit_location.y == exit.y);

    print_success("game_create");

    free_game(game);
}

static void test_player_win(void) {

    struct map_t map = load_map("./map/level1.txt");

    struct location_t start = {1, 1};
    struct location_t exit = {2, 2};

    enum resource_t resources[NB_RESOURCES];

    resources[MOVE] = 10;
    resources[WATER] = 10;
    resources[TIME] = 10;

    struct player_t *player =
        init_player(exit, resources);

    struct game_t *game =
        game_create(map, player, exit, start);

    assert(player_win(game) == 1);

    print_success("player_win");

    free_game(game);
}

static void test_move_player_wall(void) {

    struct map_t map = load_map("./map/level1.txt");

    struct location_t start = {1, 1};
    struct location_t exit = {2, 2};

    enum resource_t resources[NB_RESOURCES];

    resources[MOVE] = 10;
    resources[WATER] = 10;
    resources[TIME] = 10;

    struct player_t *player =
        init_player(start, resources);

    struct game_t *game =
        game_create(map, player, exit, start);

    int old_x = player->player_pos.x;
    int old_y = player->player_pos.y;

    move_player(game, WEST);

    assert(player->player_pos.x == old_x);
    assert(player->player_pos.y == old_y);

    print_success("move_player_wall");

    free_game(game);
}

/* ===================== MAIN ===================== */

int main(void) {

    print_section("MAP TESTS");

    test_load_map();

    print_section("PLAYER TESTS");

    test_init_player();
    test_player_move();

    print_section("GAME TESTS");

    test_game_create();
    test_player_win();
    test_move_player_wall();

    printf(
        GREEN
        "\n====================================\n"
        "   ALL TESTS PASSED SUCCESSFULLY\n"
        "====================================\n"
        RESET
    );

    return 0;
}
