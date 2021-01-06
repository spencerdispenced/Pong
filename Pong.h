#pragma once

#include "SDL.h"

#include "Ball.h"
#include "Paddle.h"
#include "Scoreboard.h"



class Pong
{
public:
    Pong();

    bool game_over = false;

    bool init_sdl();                                     // Initilizes and creates SDL screen components
    void draw();                                         
    bool check_state(SDL_Event event);                   // Calls paddle.check_state, checks for 'q' to quit 
    void update();                                       // updates position of objects and checks for collision between ball and paddles
    void close();

private:
    // Screen and score parameters
    const static int SCREEN_WIDTH = 900;
    const static int SCREEN_HEIGHT = 600;
    const static int MAX_SCORE = 10;                      // game ends when someone reaches this score

    // SDL components
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    SDL_Surface *m_surface;

    // Game objects
    Paddle m_left_paddle;
    Paddle m_right_paddle;
    Ball m_ball;
    Scoreboard m_scoreboard_left;
    Scoreboard m_scoreboard_right;

    void check_collisions(Paddle &paddle, Ball &ball);
    void check_score();                                  // Updates score on side wall collision and checks if MAX_SCORE was reached.
    void end_game_message();
};
