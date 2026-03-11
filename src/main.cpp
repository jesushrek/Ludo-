#include "Constants.hpp"
#include "Draw.hpp"
#include "Game.hpp" 
#include "Player.hpp"

#include <raylib.h>

int main()
{ 
    InitWindow(g_proportion, g_proportion, "Ludo");

    Game ludo {};
    while (!WindowShouldClose())
    { 
        BeginDrawing();
        ludo.draw_game();
        ludo.process_input();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
