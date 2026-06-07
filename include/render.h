#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "game.h"

#define TILE_SIZE 24

struct render_t {
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture *grass;
    SDL_Texture *flower;
    SDL_Texture *fire;
    SDL_Texture *sand;
    SDL_Texture *wall;
    SDL_Texture *player;
    SDL_Texture *exit;

    TTF_Font *font;
};

struct render_t *render_create(const char *title, int width, int height);

void render_game(struct render_t *render, struct game_t *game);

void render_destroy(struct render_t *render);

#endif