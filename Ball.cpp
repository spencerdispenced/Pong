#include "Ball.h"

#include <iostream>

#include "SDL.h"
#include "SDL_mixer.h"


Ball::Ball()
{
    reset();
    init_audio();
}



void Ball::reset()
{
    m_position.x = 400;
    m_position.y = 300;
    m_position.h = BALL_HEIGHT;
    m_position.w = BALL_WIDTH;
    m_vel_x = 5;
    m_vel_y = 0;
    m_volley_count = 0;

    m_y_dir = DOWN; // Initial Direction doesn't matter since vel is 0, adjusted on collision

    // ball changes direction after scoring, default is RIGHT
    if (m_x_dir == Direction_x::RIGHT)
        m_x_dir = Direction_x::LEFT;
   
    else
        m_x_dir = Direction_x::RIGHT;
}



void Ball::init_audio()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
        std::cerr << "Error Initilizing audio " << Mix_GetError() << std::endl;

    if (!(wall_sound = Mix_LoadWAV("Sounds/wall_hit.wav")))  // https://freesound.org/s/4360/
        std::cerr << "Error opening sound file: " << Mix_GetError() << std::endl;

    if (!(paddle_sound = Mix_LoadWAV("Sounds/paddle_hit.wav"))) // https://freesound.org/s/4391/
        std::cerr << "Error opening sound file: " << Mix_GetError() << std::endl;

    if (!(score_sound = Mix_LoadWAV("Sounds/score.wav"))) // https://freesound.org/s/263133/
        std::cerr << "Error opening sound file: " << Mix_GetError() << std::endl;
}



void Ball::play_sound(Mix_Chunk *sound)
{
    if (Mix_PlayChannel(-1, sound, 0) == -1)
    {
        std::cerr << "Error playing sound: " << Mix_GetError() << std::endl;
        return;
    }
}



void Ball::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // change color to white
    SDL_RenderFillRect(renderer, &m_position);
}



void Ball::move()
{
    // y direction movement
    if (m_y_dir == UP)
    {
        if (m_position.y > 5) // adjusted for border
            m_position.y -= m_vel_y;
        else
        {
            play_sound(wall_sound);
            m_y_dir = DOWN; // bounce the ball
        }
    }

    if (m_y_dir == DOWN)
    {
        if (m_position.y < 585)  // screen - ball = 5905
            m_position.y += m_vel_y;
        else
        {
            play_sound(wall_sound);
            m_y_dir = UP;
        }
    }

    // x direction movement
    if (m_x_dir == Direction_x::LEFT)
    {
        if (m_position.x > 5) // adjusted for border
            m_position.x -= m_vel_x;
        else
        {
            play_sound(score_sound);
            reset();
        }
    }

    if (m_x_dir == Direction_x::RIGHT)
    {
        if (m_position.x < 895)  
            m_position.x += m_vel_x;
        else
        {
            play_sound(score_sound);
            reset();
        }
    }
}



void Ball::change_direction_x()
{
    play_sound(paddle_sound); // Always play sound when reflected from paddle
    m_volley_count += 1;

    if (m_x_dir == Direction_x::LEFT)
    {
        m_position.x += 15; // moves ball outside of paddle to remove oscilation effect
        m_x_dir = Direction_x::RIGHT;
    }

    else if (m_x_dir == Direction_x::RIGHT)
    {
        m_position.x -= 15;
        m_x_dir = Direction_x::LEFT;
    }

    if (m_volley_count % 2 == 0)  // increase speed / difficulty as game goes along
        m_vel_x += 1;    
}



void Ball::update_velocity(int velocity)
{
    m_vel_y = velocity;
}



void Ball::close()
{
    Mix_FreeChunk(wall_sound);
    Mix_FreeChunk(paddle_sound);
    Mix_FreeChunk(score_sound);
    Mix_Quit();
}
