#include <string.h>

#include "../include/render.h"




static SDL_Texture *  load_img_texture(struct render_t * render, const char * path){
    SDL_Surface * img_surface = IMG_Load(path);
    if (img_surface == NULL) {
        fprintf(stderr, "Erreur IMG_Load %s : %s\n", path, IMG_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Texture * img_texture = SDL_CreateTextureFromSurface(render->renderer, img_surface);
    SDL_FreeSurface(img_surface);
    return img_texture;
}



struct render_t *render_create(const char *title, int width, int height){
    struct render_t * render = malloc(sizeof(struct render_t ));
    if(render == NULL){
        fprintf(stderr,"struct render_t allocation error\n");
        exit (EXIT_FAILURE);
    }

   if( SDL_Init(SDL_INIT_VIDEO)<0){
        fprintf(stderr,"SDL_Init error : %s\n",SDL_GetError());
        exit (EXIT_FAILURE);
   }

   if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "Erreur IMG_Init : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() != 0) {
        fprintf(stderr, "Erreur TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "stretch");

    render->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    render->renderer = SDL_CreateRenderer(
        render->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    

    render->exit = load_img_texture(render , "./display/star.png");
    render->fire = load_img_texture(render , "./display/fire.png");
    render->flower = load_img_texture(render , "./display/flower.png");
    render->grass = load_img_texture(render , "./display/grass.png");
    render->player = load_img_texture(render , "./display/player.png");
    render->sand = load_img_texture(render , "./display/sand.png");
    render ->wall = load_img_texture(render , "./display/wall.png");
    
    render->font = TTF_OpenFont("./display/PixelOperator.ttf",24);

    return render;
    
}

/*Texte affiché en cas de victoire */

static void render_text_no_win(struct render_t * render ,struct game_t * game){
    /*AFFichage des scores*/
    
    int window_w;
    int window_h;

    SDL_GetWindowSize(render->window, &window_w, &window_h);

    int hud_height = 80;

    
    int tile_h = (window_h - hud_height) / game->map.height;
    char move[4];
    char time[4];
    char water[4];
    snprintf(move,4,"%d",game->player->resources[MOVE]);
    snprintf(time,4,"%d",game->player->resources[TIME]);
    snprintf(water,4,"%d",game->player->resources[WATER]);
    char score[100] = "";
    strcat(score,"MOVE: ");
    strcat(score,move);

    strcat(score,"  TIME: ");
    strcat(score,time);

    strcat(score,"  Water: ");
    strcat(score,water);

    SDL_Color color = {0,0,255,0};
    SDL_Surface * ttf_surface = TTF_RenderText_Solid(render->font , score , color);
    SDL_Texture * ttf_texture = SDL_CreateTextureFromSurface(render->renderer , ttf_surface);

    SDL_Rect rect = {0,game->map.height*tile_h+20,ttf_surface->w,ttf_surface->h};
    SDL_FreeSurface(ttf_surface);
    SDL_RenderCopy(render->renderer,ttf_texture,NULL,&rect);
    SDL_DestroyTexture(ttf_texture);
}


static void render_win(struct render_t * render, struct game_t * game){
    /*AFFichage des scores*/
   int window_w;
    int window_h;

    SDL_GetWindowSize(render->window, &window_w, &window_h);

    int hud_height = 80;

    
    int tile_h = (window_h - hud_height) / game->map.height;
    

    SDL_Color color = {0,255,0,0};
    SDL_Surface * ttf_surface = TTF_RenderText_Solid(render->font , "YOU WIN !!!" , color);
    SDL_Texture * ttf_texture = SDL_CreateTextureFromSurface(render->renderer , ttf_surface);

    SDL_Rect rect = {0,game->map.height*tile_h+20,ttf_surface->w,ttf_surface->h};
    SDL_FreeSurface(ttf_surface);
    SDL_RenderCopy(render->renderer,ttf_texture,NULL,&rect);
    SDL_DestroyTexture(ttf_texture);
}

static void render_no_move_or_time(struct render_t * render, struct game_t * game){
    /*AFFichage des scores*/
   
    int window_w;
    int window_h;

    SDL_GetWindowSize(render->window, &window_w, &window_h);

    int hud_height = 80;

    
    int tile_h = (window_h - hud_height) / game->map.height;        

    SDL_Color color = {255,255,255,0};
    SDL_Surface * ttf_surface = TTF_RenderText_Solid(render->font , "YOU FAIL !!!" , color);
    SDL_Texture * ttf_texture = SDL_CreateTextureFromSurface(render->renderer , ttf_surface);

    SDL_Rect rect = {0,game->map.height*tile_h+20,ttf_surface->w,ttf_surface->h};
    SDL_FreeSurface(ttf_surface);
    SDL_RenderCopy(render->renderer,ttf_texture,NULL,&rect);
    SDL_DestroyTexture(ttf_texture);
}

void render_game(struct render_t *render, struct game_t *game,int win){
    int window_w;
    int window_h;

    SDL_GetWindowSize(render->window, &window_w, &window_h);

    int hud_height = 80;

    int tile_w = window_w / game->map.width;
    int tile_h = (window_h - hud_height) / game->map.height;

    SDL_SetRenderDrawColor(render->renderer,0,0,0,255);
    SDL_RenderClear(render->renderer);
    for(int j=0;j<game->map.height;j++){
        for(int i=0;i<game->map.width;i++){
            if(game->player->player_pos.x == i && game->player->player_pos.y == j ){
                SDL_Rect rect = {i*tile_w,j*tile_h,tile_w,tile_h};
                SDL_RenderCopy(render->renderer,render->player,NULL,&rect);
            }
            else if (game->exit_location.x == i && game->exit_location.y == j)
            {
                SDL_Rect rect = {i*tile_w,j*tile_h,tile_w,tile_h};
                SDL_RenderCopy(render->renderer,render->exit,NULL,&rect);
            }
            
            else{
                switch(game->map.grid[j][i]){
                    case GRASS:
                        SDL_Rect rect = {i*tile_w,j*tile_h,tile_w,tile_h};
                        SDL_RenderCopy(render->renderer,render->grass,NULL,&rect);
                        break;
                    case FLOWER:
                        SDL_Rect rect1 = {i*tile_w,j*tile_h,tile_w,tile_h};
                        SDL_RenderCopy(render->renderer,render->flower,NULL,&rect1);
                        break;
                    case FIRE:
                        SDL_Rect rect2 = {i*tile_w,j*tile_h,tile_w,tile_h};
                        SDL_RenderCopy(render->renderer,render->fire,NULL,&rect2);
                        break;
                    case SAND:
                        SDL_Rect rect3 = {i*tile_w,j*tile_h,tile_w,tile_h};
                        SDL_RenderCopy(render->renderer,render->sand,NULL,&rect3);
                        break;
                    case WALL:
                        SDL_Rect rect4 = {i*tile_w,j*tile_h,tile_w,tile_h};
                        SDL_RenderCopy(render->renderer,render->wall,NULL,&rect4);
                        break;
                    default:
                        break;
                    
                }
            }
        }
    }
    SDL_SetRenderDrawColor(render->renderer,255,255,255,255);
   SDL_RenderDrawLine(
    render->renderer,
    0,
    game->map.height * tile_h + 10,
    game->map.width * tile_w,
    game->map.height * tile_h + 10
    );

    if(game->player->resources[TIME] == 0 || game->player->resources[MOVE] == 0)
        render_no_move_or_time(render,game);
    else if(!win){
        render_text_no_win(render,game);
    } 
    else
        render_win(render,game);
    


    
    SDL_RenderPresent(render->renderer);
}

void render_destroy(struct render_t *render) {
    SDL_DestroyTexture(render->exit);
    SDL_DestroyTexture(render->fire);
    SDL_DestroyTexture(render->flower);
    SDL_DestroyTexture(render->grass);
    SDL_DestroyTexture(render->player);
    SDL_DestroyTexture(render->sand);
    SDL_DestroyTexture(render->wall);

    TTF_CloseFont(render->font);

    SDL_DestroyRenderer(render->renderer);
    SDL_DestroyWindow(render->window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    free(render);
}