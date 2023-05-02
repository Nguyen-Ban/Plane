#ifndef COMMON_H_
#define COMMON_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "LTexture.h"
#include "TextObject.h"


static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Surface* gSurface = NULL;

static const int SCREEN_HEIGHT = 750;
static const int SCREEN_WIDTH = 1200;
static const int DOT_WIDTH = 95;
static const int DOT_HEIGHT = 79;

const int NUM_THREATS = 5;

const int LIFE_POINTS = 3;

bool checkCollision(SDL_Rect &a, SDL_Rect &b);
int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font,
                            const std::string& menu1,
                            const std::string& menu2,
                            const std::string& img_name);
#endif // COMMON_H_

