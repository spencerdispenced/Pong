#pragma once

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"


class Scoreboard
{
public:
    Scoreboard(int x, int y);                       // Opens font and sets position 
    void draw(SDL_Renderer* renderer, int score);
    void draw(SDL_Renderer * renderer, int score, int lose_score, std::string side);
    void close();

private:
    TTF_Font *m_scorefont;
    SDL_Surface *m_surface;
    SDL_Texture *m_texture;
    SDL_Rect m_rect;
};

