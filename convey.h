#ifndef CONVEY_H
#define CONVEY_H
#include <SDL2/SDL.h>
void changeboard(int x, int y);
void printm();
void fill_n();
void process();
void drawm(SDL_Renderer *renderer);
int calculate_n(int x, int y);


#endif