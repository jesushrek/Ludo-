#include "../Constants.hpp"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "../gameLoop.cpp"

constexpr float _paddingX { 1.7 };
constexpr float _paddingY { 1.7 };
constexpr float _fontSize { 20 };

constexpr char _player_label[] = { "4;3;2"};

Rectangle get_rectangle(int x, int y, const char* text, int override_x, int override_y)
{ 
    int text_width = GetTextWidth(text);

    int final_x = (override_x > 0)? override_x : text_width * _paddingX * _fontSize;
    int final_y = (override_y > 0)? override_y : _fontSize * _paddingY * _fontSize;

    return (Rectangle) { 
        (float) x, 
        (float) y, 
        (float) final_x + _fontSize,
        (float) final_y + _fontSize
    };
}

bool play_button()
{ 
    return GuiButton(get_rectangle(g_proportion / 2, 
                g_proportion / 2 - 40, "Play", 50, 20), "Play");
}

//GuiDropdownBox(Rectangle bounds, const char *text, int *active, bool editMode); // Dropdown Box control, returns selected item
void drop_down(int* active)
{ 
    static bool editMode = false;
    GuiLabel(get_rectangle(g_proportion/2, g_proportion/2 - _fontSize * _paddingY, "Players", 0, 0), "Players");
    if (GuiDropdownBox(get_rectangle(g_proportion/2, (g_proportion/2), " ", 50, 20), _player_label, active, editMode))
    { 
        editMode = !editMode;
    }
}

int main() 
{ 
    InitWindow(g_proportion, g_proportion, "Ludo - UI");
    SetTargetFPS(60);

    int player_dropdown{};
    bool can_break{};
    Game game{};

    GuiSetStyle(DEFAULT, TEXT_SIZE, _fontSize);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));

    bool kill = false;
    while (!kill)
    {
        //Rectangle get_rectangle(int x, int y, const char* text, int override_x, int override_y)
        GuiLabel({ 0, 0, 300, _fontSize }, "Kushma-Ludo");
        kill = WindowShouldClose();
        int player_count { 
            (player_dropdown == 0)? 4 : ((player_dropdown == 1)? 3 : 2)
        };

        for (int idx = 3; idx >= player_count; --idx)
            game.modify_player(idx).set_won();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        drop_down(&player_dropdown);
        if (play_button()) 
        {
            printf("%d\n", player_count);
            game_loop(game, &kill);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
