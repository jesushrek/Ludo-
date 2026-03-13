#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <raylib.h>

enum Colors { 
    Red,
    Green,
    Yellow,
    Blue,
};

constexpr int g_proportion { 600 };
constexpr int g_board_proportions { 15 };
constexpr int g_size { g_proportion / g_board_proportions };

constexpr Vector2 homeStretch[][6] {
    { { 1, 7 }, { 2, 7 }, { 3, 7 }, { 4, 7 }, { 5, 7 }, { 6, 7 } },
        { { 7, 1 }, { 7, 2 }, { 7, 3 }, { 7, 4 }, { 7, 5 }, { 7, 6 } },
        { { 13, 7 }, { 12, 7 }, { 11, 7 }, { 10, 7 }, { 9, 7 }, { 8, 7 } },
        { { 7, 13 }, { 7, 12 }, { 7, 11 }, { 7, 10 }, { 7, 9 }, { 7, 8 } }
};

constexpr Color colors[] { 
    RED,
        GREEN,
        YELLOW,
        BLUE,
};

constexpr Vector2 home_offset[]
{ 
    { 0, 0 }, //red
        { 9, 0 }, //green
        { 9, 9 },
        { 0, 9 },
};

constexpr Vector2 start_point[]
{ 
    { 1, 6 },
        { 8, 1 },
        {13, 8 },
        {6, 13 },
};

constexpr Vector2 safe_point[]
{
    { 2, 8 },
        { 6, 2 },
        { 12, 6},
        { 8, 12},
};

constexpr Vector2 global_path[]
{ 
    { 1, 6 }, { 2, 6 }, { 3, 6 }, { 4, 6 }, { 5, 6 },             // Red to green
        { 6, 5 }, { 6, 4 }, { 6, 3 }, { 6, 2 }, { 6, 1 }, { 6, 0 },   // to Green's side
        { 7, 0 }, { 8, 0 }, // towards green's start
        { 8, 1 }, { 8, 2 }, { 8, 3 }, { 8, 4 }, { 8, 5 },            // green to yellow
        { 9, 6 }, { 10, 6}, { 11, 6}, { 12, 6}, { 13, 6}, { 14, 6},  // to yellow's side
        { 14, 7}, { 14, 8}, // towards yellow's start
        { 13, 8}, { 12, 8}, { 11, 8}, { 10, 8}, { 9, 8 },             // yellow to blue
        { 8, 9 }, { 8, 10}, { 8, 11}, { 8, 12}, { 8, 13}, { 8, 14 },  // to blue's side
        { 7, 14}, { 6, 14}, // towards blue's start
        { 6, 13}, { 6, 12}, { 6, 11}, { 6, 10}, { 6, 9 },             // blue to red
        { 5, 8 }, { 4, 8 }, { 3, 8 }, { 2, 8 }, { 1, 8 }, { 0, 8 },   // to red's side
        { 0, 7 }, { 0, 6 },                                           // to red's safe 
};

constexpr float m_skip_delay { 20.5f };

#endif
