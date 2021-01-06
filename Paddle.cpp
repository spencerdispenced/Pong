#include "Paddle.h"

#include "SDL.h"


Paddle::Paddle(Side side)
{
    m_side = side;
    m_dir = Direction::NONE;

    if (m_side == Side::LEFT)
    {
        m_rect.x = 100;
        m_rect.y = 250;
        m_rect.h = PADDLE_HEIGHT;
        m_rect.w = PADDLE_WIDTH;
    }

    if (m_side == Side::RIGHT)
    {
        m_rect.x = 800;
        m_rect.y = 250;
        m_rect.h = PADDLE_HEIGHT;
        m_rect.w = PADDLE_WIDTH;
    }
}



bool Paddle::check_state(SDL_Event const &event)
{
    if (event.type == SDL_KEYDOWN )
    {
        const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
            
        if (currentKeyStates[SDL_SCANCODE_Q]) // Quit if 'q' is pressed
        {
            SDL_Quit();
            return false;
        }
    
        /* Left paddle controls */
        else if (m_side == Side::LEFT)  
        { 
            if (currentKeyStates[SDL_SCANCODE_W])
                m_dir = Direction::UP;
            
            if (currentKeyStates[SDL_SCANCODE_Z])
                m_dir = Direction::DOWN;          
        }

        /* Right paddle controls */
        else if (m_side == Side::RIGHT)
        {
            if (currentKeyStates[SDL_SCANCODE_UP])
                m_dir = Direction::UP;
            
            if (currentKeyStates[SDL_SCANCODE_DOWN])
                m_dir = Direction::DOWN;         
        }
    }
        
    /* Hold to move paddle */
    //else if (event.type == SDL_KEYUP)
        //m_dir = Direction::NONE;

    return true;
}



void Paddle::move()
{
    if (m_dir == Direction::UP)
    {
        if (m_rect.y > 5)
            m_rect.y -= 5;
    }

    if (m_dir == Direction::DOWN)
    {
        if (m_rect.y < 495)  // screen - paddle = 500, so top of paddle doesn't go off screen, adjusted for border
            m_rect.y += 5;
    }
}



void Paddle::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 34, 35, 36, 0); // change color to dark gray
    SDL_RenderFillRect(renderer, &m_rect);
}
