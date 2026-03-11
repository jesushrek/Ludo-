#ifndef DRAW_HPP
#define DRAW_HPP

#include "Constants.hpp"

#include <raylib.h>
#include <iostream>

void draw_home_stretch()
{ 
    for (int color_idx = 0; color_idx < 4; ++color_idx)
    {
        for (int i = 0; i < 6; ++i)
        {
            float x { homeStretch[color_idx][i].x * g_size };
            float y { homeStretch[color_idx][i].y * g_size };
            DrawRectangle(x, y, g_size, g_size, colors[color_idx]); 
            DrawRectangleLines(x, y, g_size, g_size, LIGHTGRAY); 
        }
    }
}

void draw_dice(int value, Vector2 pos, int size)
{ 
    DrawRectangleRounded({ pos.x + 4, pos.y + 4, static_cast<float>(size), static_cast<float>(size) }, 0.2f, 10, DARKGRAY);
    DrawRectangleRounded({ pos.x, pos.y, static_cast<float>(size), static_cast<float>(size) }, 0.2f, 10, RAYWHITE);
    DrawRectangleRoundedLines({ pos.x, pos.y, static_cast<float>(size), static_cast<float>(size) }, 0.2f, 10, RAYWHITE);

    if (value == 0) return;
    float mid { size / 2.0f };
    float low  { size / 4.0f };
    float high  { size * 0.75f };
    float radius { size * 0.08f };

    auto dot = [&](float dx, float dy) { 
        DrawCircle(pos.x + dx, pos.y + dy, radius, BLACK);
    };

    if (value % 2 != 0) dot(mid, mid);

    if (value > 1) 
    {
        dot(low, low); // top left
        dot(high, high); // bottom right;
    }

    if (value > 3)
    { 
        dot(high, low); // top right 
        dot(low, high); // bottom left
    }

    if (value == 6)
    { 
        dot(low, mid); // mid left
        dot(high, mid); // mid right
    }
}

void draw_ludo_pawn(Vector2 position, Color color, float jumpY)
{ 
    //base / shadow position
    Vector2 basePos { position };
    //pawn position when jumping
    Vector2 pawnPos { position.x, position.y - jumpY };
    //shadow
    DrawEllipse(basePos.x, basePos.y + 10, 15, 5, Fade(BLACK, 0.2f));
    // skirt / base 
    DrawCircleSector(
            Vector2 { pawnPos.x, pawnPos.y + 10 }, 18, 180, 360, 20, color);
    //body
    DrawRectangle(pawnPos.x - 5, pawnPos.y - 10, 10, 15, color);
    //head
    DrawCircle(pawnPos.x, pawnPos.y - 12, 10, color);
    //outline
    DrawCircleLines(pawnPos.x, pawnPos.y - 12, 10, Fade(BLACK, 0.3f));
}

void draw_spawn()
{ 
    float padding { 1.5f };
    for (int p = 0; p < 4; ++p)
    { 
        for (int i = 0; i < 4; ++i)
        { 
            int local_x { i % 2 };
            int local_y { i / 2 };

            float x { (home_offset[p].x + (local_x * 3.0f) + padding) * g_size };
            float y { (home_offset[p].y + (local_y * 3.0f) + padding) * g_size };

            DrawCircle(x, y, g_size * 0.75f, WHITE);
            DrawCircleLines(x, y, g_size * 0.76f, BLACK);
        }
    }
}

void draw_start_points()
{ 
    for (int color_idx = 0; color_idx < 4; ++color_idx)
    { 
        float x { start_point[color_idx].x * g_size };
        float y { start_point[color_idx].y * g_size };

        DrawRectangle(x, y, g_size, g_size, colors[color_idx]); 
        DrawRectangleLines(x, y, g_size, g_size, LIGHTGRAY); 
    }
}

void draw_safe_points()
{
    for (int idx = 0; idx < 4; ++idx)
    { 
        float x { (safe_point[idx].x * g_size) + g_size / 2 };
        float y { (safe_point[idx].y * g_size) + g_size / 2 };

        DrawPolyLines({x, y}, 5, g_size * 0.4, 0.5, BLACK);
    }
}

void draw_board()
{ 
    for (int row = 0; row < g_board_proportions; ++row)
    { 
        for (int column = 0; column < g_board_proportions; ++column)
        { 
            Color tile_color { RAYWHITE };

            if (row == 6 && column == 8)
                tile_color = GREEN;

            else if (row == 8 && column == 8)
                tile_color = YELLOW;

            else if (row == 8 && column == 6)
                tile_color = BLUE;

            else if (row == 6 && column == 6)
                tile_color = RED;

            else if (row < 6 && column < 6)
                tile_color = RED;

            else if (row < 6 && column > 8)
                tile_color = GREEN;

            else if (row > 8 && column < 6)
                tile_color = BLUE;

            else if (row > 8 && column > 8)
                tile_color = YELLOW;

            DrawRectangle(column * g_size, row * g_size, g_size, g_size, tile_color);
            DrawRectangleLines(column * g_size, row * g_size, g_size, g_size, LIGHTGRAY);
        }
    }

    draw_start_points();
    draw_spawn();
    draw_home_stretch();
    draw_safe_points();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    { 
        Vector2 mouse_pos { GetMousePosition() };
        std::cout <<  (int)(mouse_pos.x / g_size) << ", " << (int)(mouse_pos.y / g_size) << '\n';
    }
}
#endif 
