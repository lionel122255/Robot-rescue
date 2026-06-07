#include "../include/map.h"


struct map_t load_map(const char * filename){
    struct map_t res;
    FILE * f = fopen(filename,"r");
    if(f == NULL){
        fprintf(stderr,"Error opening file %s\n",filename);
        exit(1);
    }

    int width , height ;
    fscanf(f,"%d %d",&width,&height);

    res.grid = malloc(sizeof(enum ground_t*)*height);
    for(int i = 0;i<height;i++){
        res.grid[i] = malloc(sizeof(enum ground_t)*width);
        for(int j = 0;j<width;j++){
            int tmp ;
            fscanf(f,"%d",&tmp);
            res.grid[i][j] = (enum ground_t)tmp;
        }
    }
    res.width = width;
    res.height = height;
    fclose(f);
    return res;
}

