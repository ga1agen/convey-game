#include "convey.h"

#define WIDTH 50
#define HEIGHT 50

static int m[WIDTH][HEIGHT] = {
    {0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}
};
static int n[WIDTH][HEIGHT] = {0};

/* 
void printm(){
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < WIDTH; j++)
            if(m[i][j] == 1)
                printf("%c ", 'K');
            else printf("%c ", '_');
        printf("\n");
    }
}
*/

void changeboard(int x, int y){
    if((x == 0) || (y == 0))
        return;
    int j = (x / 5) - 1;
    int i = (y / 5) - 1;
    if(x % 5 != 0)
        j += 1;
    if(y % 5 != 0)
        i += 1;
    if(m[i][j] == 1)
        m[i][j] = 0;
    else m[i][j] = 1;
}

void drawm(SDL_Renderer *renderer){
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < WIDTH; j++){
            SDL_Rect rect = {
                .x = j * 5,
                .y = i * 5,
                .w = 5,
                .h = 5
            };
            if(m[i][j] == 1){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }    
            else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }       
    }
}

void fill_n(){
    for(int i = 0; i < WIDTH; i++)
        for(int j = 0; j < WIDTH; j++)
            n[i][j] = calculate_n(i, j);
}

void process(){
    for(int i = 0; i < WIDTH; i++)
        for(int j = 0; j < WIDTH; j++)
            switch(m[i][j]){
                case 1:
                    if(n[i][j] >= 4)
                        m[i][j] = 0;
                    if(n[i][j] <= 1)
                        m[i][j] = 0;
                    break;
                case 0:
                    if(n[i][j] == 3)
                        m[i][j] = 1;
                break;
            }
}

int calculate_n(int x, int y){
    int count = 0;
    for(int i = x - 1; i <= x + 1; i++)
        if(!((i < 0) || (i > WIDTH - 1)))
            for(int j = y - 1; j <= y + 1; j++)
                if(!((j < 0) || (j > HEIGHT - 1)))
                        if(m[i][j] == 1) 
                            count += 1;
    if(m[x][y] == 1) count--;
    return count;
}