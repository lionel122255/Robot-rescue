#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../include/map.h"
#include "../include/player.h"
#include "../include/game.h"
#include "../include/render.h"

#define WINDOW_EXTRA_HEIGHT 80
#define TIMER 2000


int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    struct map_t map = load_map(argv[1]);
    struct location_t initial_pos ={1,1};
    struct location_t exit_pos = {map.width-2,map.height-2};
    enum resource_t player_res[NB_RESOURCES];
    player_res[MOVE] = map.width + map.height ;
    player_res[TIME] = TIMER;
    player_res[WATER] = 2;
   
    struct player_t * player  = init_player(initial_pos,player_res);

    struct game_t * game = game_create(map,player,exit_pos,initial_pos);

    struct render_t * render = render_create("Robo-rescue" , map.width * TILE_SIZE , 
                                map.height*TILE_SIZE +WINDOW_EXTRA_HEIGHT);

    int running =1;
    SDL_Event event ;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Erreur SDL_mixer : %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

        // 1. Charger la musique
   Mix_Music *musique = Mix_LoadMUS("./display/Can't Stop Winning MP3.mp3");

    if (musique == NULL) {
        fprintf(stderr, "Erreur chargement musique : %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    /* boucle infinie */
    Mix_PlayMusic(musique, -1);

    while(running /*&& !player_win(game)*/){
        game->player->resources[TIME] --;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_m){
                    
                        // On vérifie l'état actuel de la musique
                        if(Mix_PausedMusic() == 1){
                            // Si elle était en pause, on la relance
                            Mix_ResumeMusic();
                        } else {
                            // Sinon, on la met en pause
                            Mix_PauseMusic();
                        }
                    
                    }


                    if(event.key.keysym.sym == SDLK_UP)
                        move_player(game,NORTH);
                    if(event.key.keysym.sym == SDLK_DOWN)
                        move_player(game,SOUTH);
                    if(event.key.keysym.sym == SDLK_RIGHT)
                        move_player(game,EAST);
                    if(event.key.keysym.sym == SDLK_LEFT)
                        move_player(game,WEST);
                    break;
                default:
                    break;
                    
            }
        }
        render_game(render,game,player_win(game));
        if(player_win(game) || game->player->resources[TIME] ==0 || game->player->resources[MOVE] == 0){
            running=0;
            SDL_Delay(100);
        }
            
        SDL_Delay(16);
    }

    Mix_FreeMusic(musique);
    Mix_CloseAudio();
    render_destroy(render);
    free_game(game);
    

    


    return 0;
}