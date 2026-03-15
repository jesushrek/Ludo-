#include "../Constants.hpp"
#include "../Draw.hpp"
#include "../Game.hpp" 
#include "../Player.hpp"

#include <raylib.h>

void game_loop(Game ludo, bool* kill, bool* finished)
{ 
    while (!*(kill) | *(finished))
    { 
        *kill = WindowShouldClose();
        ludo.draw_game();
        ludo.process_input();
        EndDrawing();

        int is_winner_counter {0};
        for (int i = 0; i < 4; ++i)
        { 
            if (ludo.m_players[i].is_winner())
                ++is_winner_counter;
        }

        if (is_winner_counter == 3)
        {
            *finished = true;
            break;
        }
    }
}
