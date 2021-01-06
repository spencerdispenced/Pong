#include "Scoreboard.h"

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"


Scoreboard::Scoreboard(int x, int y)
{
    if (TTF_Init() < 0)  // Initialize SDL_TTF
        return;

    if (!(m_scorefont = TTF_OpenFont("Fonts/DejaVuSansMono.ttf", 40)))
        std::cout << TTF_GetError() << std::endl;

    m_rect.x = x;
    m_rect.y = y;
}



void Scoreboard::draw(SDL_Renderer* renderer, int s)
{
    std::string score = std::to_string(s);
    
    if (!(m_surface = TTF_RenderText_Solid(m_scorefont, score.c_str(), { 255, 255, 255, 255 })))
        std::cout << TTF_GetError() << std::endl;

    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
    SDL_FreeSurface(m_surface);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h);
    SDL_SetRenderTarget(renderer, m_texture);

    SDL_RenderCopy(renderer, m_texture, nullptr, &m_rect);
    SDL_DestroyTexture(m_texture);
}



void Scoreboard::draw(SDL_Renderer* renderer, int win_score, int lose_score, std::string side)
{
    std::string w = std::to_string(win_score);
    std::string l = std::to_string(lose_score);
    std::string message = "Winner is:   " + side + " " + w + " to " + l;

    if (!(m_surface = TTF_RenderText_Solid(m_scorefont, message.c_str(), { 255, 128, 0, 0 })))
        std::cout << TTF_GetError() << std::endl;

    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
    SDL_FreeSurface(m_surface);

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h);
    SDL_SetRenderTarget(renderer, m_texture);

    SDL_RenderCopy(renderer, m_texture, nullptr, &m_rect);
    SDL_DestroyTexture(m_texture);
}



void Scoreboard::close()
{
    TTF_CloseFont(m_scorefont);
    SDL_DestroyTexture(m_texture);
    TTF_Quit();
}
