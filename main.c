#include <stdio.h>
#include <SDL2/SDL.h>
#include "convey.h"

const int WIDTH = 250, HEIGHT = 250;

int main(int argc, char *argv[]) {
  int quit = 0;
  int be = 0;
  SDL_Window *window;
  SDL_Renderer *renderer;
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow("Hello, World!",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WIDTH, HEIGHT,
                                        SDL_WINDOW_ALLOW_HIGHDPI);
  if(window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);

  SDL_Event event;
  while(!quit) {
    if(SDL_PollEvent(&event)) {
      switch(event.type){
        case SDL_QUIT:
            quit = 1;
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button){
                case SDL_BUTTON_LEFT:
                    if(!be)
                        changeboard(event.motion.x, event.motion.y);
                    break;
                case SDL_BUTTON_MIDDLE:
                    if(be)
                        be = 0;
                    else
                        be = 1;
                    break;
                case SDL_BUTTON_RIGHT:
                    if(!be){
                        fill_n();
                        process();
                    }
                    break;
            }
            break;
      }
    }
    drawm(renderer);
    SDL_RenderPresent(renderer);
    if(be){
        fill_n();
        process();
        SDL_Delay(50);
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
