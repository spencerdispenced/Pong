#include <iostream>

#include "SDL.h"

#include "Pong.h"


int main(int argc, char* argv[])
{  
    Pong pong; 

    if (pong.init_sdl() == false)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    /* Main game loop */
    SDL_Event event;  
    while (pong.game_over == false)
    {
        while (SDL_PollEvent(&event) > 0)
        {
            if (pong.check_state(event) == false) // Close on pressing 'q' or closing window
            {
                pong.close();
                return 0;
            }
        }

        pong.update(); // update positions of paddles and ball
        pong.draw();  // draw the objects to the screen
    }

    // Exit game after someone wins    
    SDL_Delay(5000);
    pong.close();
    return 0;
}
