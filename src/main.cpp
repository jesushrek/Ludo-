#include "Constants.hpp"
#include "Draw.hpp"
#include "Game.hpp" 
#include "Player.hpp"

#include <raylib.h>

int main()
{ 
    InitWindow(g_proportion, g_proportion, "Ludo");
    SetTargetFPS(30);

    Game ludo {};
    while (!WindowShouldClose())
    { 
        BeginDrawing();
        ClearBackground(BLACK);
        ludo.draw_game();
        ludo.process_input();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
