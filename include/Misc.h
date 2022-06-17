#ifndef MISC_H
#define MISC_H

#include <random>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 860
#define WINDOW_HEIGHT 640

struct Colour {
    int r, g, b;
};

int randomNumberBetween(int floor, int ceiling);
int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius);
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);
float mapInteger(float num, float a, float b, float c, float d);
float euclideanDistance(float x1, float y1, float x2, float y2);

#endif