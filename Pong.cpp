#include "Pong.h"

#include <string>

#include "SDL.h"

#include "Ball.h"
#include "Paddle.h"
#include "Scoreboard.h"


Pong::Pong() :
    m_window(NULL), m_renderer(NULL), m_texture(NULL), m_surface(NULL),
    m_left_paddle(Paddle::Side::LEFT), m_right_paddle(Paddle::Side::RIGHT), m_ball(),
    m_scoreboard_left(30, 0), m_scoreboard_right(850, 0)
{}



bool Pong::init_sdl()
{
    /* Starting SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)  // Intitilize SDL
        return false;    
    
    /* Create a window */
    if (!(m_window = SDL_CreateWindow
                     ("Spencers Pong Game",
                      SDL_WINDOWPOS_CENTERED,
                      SDL_WINDOWPOS_CENTERED,
                      SCREEN_WIDTH,
                      SCREEN_HEIGHT,
                      SDL_WINDOW_SHOWN)))
    {
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    /* Create a render */
    if (!(m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
    {
        SDL_DestroyWindow(m_window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    /* Load a bitmap image */
    if (!(m_surface = SDL_LoadBMP("Images/game_board.bmp")))
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    /* Upload surface to render, then free surface*/
    if (!(m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface)))
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    SDL_FreeSurface(m_surface);

    return true;
}



void Pong::draw()
{   
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);  // Draw background image 

    // Draw various game objects
    m_left_paddle.draw(m_renderer);
    m_right_paddle.draw(m_renderer);
    m_ball.draw(m_renderer);

    // Check score and draw scorboards
    check_score();
    m_scoreboard_left.draw(m_renderer, m_left_paddle.score);
    m_scoreboard_right.draw(m_renderer, m_right_paddle.score);

    SDL_RenderPresent(m_renderer);  // Show render on window
}



bool Pong::check_state(SDL_Event event)
{ 
    // Check for 'q' press to quit game 
    if (!m_right_paddle.check_state(event) || event.type == SDL_QUIT)
        return false;
    
    m_left_paddle.check_state(event);

    return true;
}



void Pong::update()
{
    m_left_paddle.move();
    m_right_paddle.move();

    m_ball.move(); 
       
    if (SDL_HasIntersection(&m_left_paddle.m_rect, &m_ball.m_position))
        check_collisions(m_left_paddle, m_ball);

    if (SDL_HasIntersection(&m_right_paddle.m_rect, &m_ball.m_position))
        check_collisions(m_right_paddle, m_ball);        
}



void Pong::check_collisions(Paddle &paddle, Ball &ball)
{
    ball.change_direction_x(); // ball always gets reflected off paddle
    
    if (ball.m_position.y < (paddle.m_rect.y) + 20) // upper quarter of paddle 0-19
    {
        ball.m_y_dir = ball.UP;
        ball.update_velocity(5);
    }
    
    else if (ball.m_position.y <= ((paddle.m_rect.y) + 20) && ball.m_position.y < (paddle.m_rect.y) + 50) // upper middle quarter 20-49
    {
        ball.m_y_dir = ball.UP;
        ball.update_velocity(2);
    }
    
    else if (ball.m_position.y <= ((paddle.m_rect.y) + 50) && ball.m_position.y < (paddle.m_rect.y) + 80) // lower middle quarter 50-79
    {
        ball.m_y_dir = ball.DOWN;
        ball.update_velocity(2);
    }
    
    else if (ball.m_position.y < ((paddle.m_rect.y) + 81) && ball.m_position.y < (paddle.m_rect.y) + paddle.PADDLE_HEIGHT) // lower quarter 80-100
    {
        ball.m_y_dir = ball.DOWN;
        ball.update_velocity(5);
    }   
}



void Pong::check_score()
{
    if (m_left_paddle.score == MAX_SCORE || m_right_paddle.score == MAX_SCORE) // game ends after reaching max score
    {
        end_game_message();
        game_over = true;
    }

    if (m_ball.m_position.x <= 5) // if ball hits left wall, right paddle scores
        m_right_paddle.score += 1;

    else if (m_ball.m_position.x >= SCREEN_WIDTH-5) // if ball hits right wall, left paddle scores
        m_left_paddle.score += 1;
}



void Pong::end_game_message()
{
    std::string side;
    int winner;
    int loser;

    if (m_left_paddle.score == MAX_SCORE)
    {
        side = "Left";
        winner = m_left_paddle.score;
        loser = m_right_paddle.score;

    }

    if (m_right_paddle.score == MAX_SCORE)
    {
        side = "Right";
        winner = m_right_paddle.score;
        loser = m_left_paddle.score;
    }
           
    Scoreboard message(175, 250); // Approximate middle of screen
    message.draw(m_renderer, winner, loser, side);
    message.close();
}



void Pong::close()
{
    // Free all objects     
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyWindow(m_window);

    m_ball.close();
    m_scoreboard_left.close();
    m_scoreboard_right.close();
    SDL_Quit();
}
