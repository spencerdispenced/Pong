#pragma once

#include "SDL.h"
#include "SDL_mixer.h"


class Ball
{
public:
    Ball();

    enum Direction_y { NONE, UP, DOWN };
    enum class Direction_x { NONE, LEFT, RIGHT };
    const int BALL_HEIGHT = 10;
    const int BALL_WIDTH = 10;
    SDL_Rect m_position;

    Direction_x m_x_dir;
    Direction_y m_y_dir;

    void draw(SDL_Renderer *renderer);
    void move();                               // Updates position of ball and reflects off top and bottom
    void change_direction_x();                 // Changes 'x' direction on contact with paddle
    void update_velocity(int velocity);        // Changes 'y' velocity, or 'angle' of ball after contact
    void close();

private:
    int m_vel_x;
    int m_vel_y;
    int m_volley_count;

    Mix_Chunk *wall_sound;
    Mix_Chunk *paddle_sound;
    Mix_Chunk *score_sound;

    void reset();                               // Sets ball to initial starting parameters
    void init_audio();                          // Initilizes Mixer and loads audio files
    void play_sound(Mix_Chunk *sound);
};

