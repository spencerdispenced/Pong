#pragma once

#include "SDL.h"


class Paddle
{
public:
    enum class Direction { NONE, UP, DOWN };
    enum class Side { LEFT, RIGHT };
    Paddle(Side side);
    const int PADDLE_HEIGHT = 100;
    const int PADDLE_WIDTH = 15;
    SDL_Rect m_rect;
    int score = 0;

    bool check_state(SDL_Event const &event);        // Checks for key presses and changes direction accordingly
    void move();                                     // Used to continuously update position of paddle
    void draw(SDL_Renderer *renderer);

private:
    Direction m_dir;
    Side m_side;
};
