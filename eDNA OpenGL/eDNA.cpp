#define STB_IMAGE_IMPLEMENTATION

#include "Game.h"


int main()
{
    Game game;

    while (game.Running())
    {
        game.ProcessInputs();
        game.Update();
        game.Render();
    }
    game.Exit();

    return 0;
}

