#ifndef MISC_H
#define MISC_H

#include <random>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

int randomNumberBetween(int floor, int ceiling);
int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius);
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

#endif