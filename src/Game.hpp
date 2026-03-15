#ifndef GAME_HPP
#define GAME_HPP

#include "Constants.hpp"
#include "Player.hpp"

#include <raylib.h>

bool is_yard(int player_id, Vector2 pos)
{ 
    int cx { static_cast<int>(pos.x) };
    int cy { static_cast<int>(pos.y) };

    if (player_id == 0)
        if (cy < 6 && cx < 6) return true;
    if (player_id == 1)
        if (cy < 6 && cx > 8) return true;
    if (player_id == 3)
        if (cy > 8 && cx < 6) return true;
    if (player_id == 2)
        if (cy > 8 && cx > 8) return true;

    return false;
}

bool is_tile_safe(Vector2 pos)
{ 
    bool is_safe = false;
    for (int i = 0; i < 4; ++i)
    { 
        if (safe_point[i].x == pos.x && safe_point[i].y == pos.y)
            is_safe = true;
    }

    for (int i = 0; i < 4; ++i)
    { 
        if (start_point[i].x == pos.x && start_point[i].y == pos.y)
            is_safe = true;
    }

    return is_safe;
}

class Game 
{ 
    private:
        Player m_players[4];
        int m_current_turn{};
        int m_dice_roll{};
        bool m_has_rolled{};
    public:
        Game()
            :m_players { 0, 1, 2, 3 }
        ,m_current_turn {0} // start with red
        ,m_dice_roll {0}
        ,m_has_rolled { false }
        {
            m_players[0].set_turn(true);
        }

        Player& modify_player(int idx)
        { 
            return m_players[idx];
        }

        void roll_dice()
        { 
            if (!m_has_rolled)
            { 
                m_dice_roll  = GetRandomValue(1, 6);
                m_has_rolled = true;
            }
        }

        void update_game_logic()
        { 
            static float skip_timer{};

            if (skip_timer >= m_skip_delay)
                skip_timer = 0.0f;

            float delta_time { GetFrameTime() + 1.0f };

            if (m_has_rolled && !is_valid())
            { 
                skip_timer += delta_time;
                if (skip_timer >= m_skip_delay)
                { 
                    resolve_turn(false, false);
                }
            }
        }

        void move_to_next_turn()
        { 
            m_players[m_current_turn].set_turn(false);
            int safety_counter = 0;
            do 
            { 
                m_current_turn = (m_current_turn + 1) % 4;
                ++safety_counter;
            } while(m_players[m_current_turn].is_winner() && safety_counter < 4);

            m_players[m_current_turn].set_turn(true);
            m_has_rolled = false;
            m_dice_roll = 0;
        }

        void resolve_turn(bool isKilled, bool is_finished)
        { 
            if (m_dice_roll == 1 || m_dice_roll == 6 || isKilled || is_finished)
            {
                if (m_players[m_current_turn].is_winner())
                { 
                    move_to_next_turn();
                }
                else 
                {
                    m_has_rolled = false;
                    m_dice_roll = 0;
                }
            }
            else 
            { 
                move_to_next_turn();
            }
        }
        /*
           bool isItOrNot { false };
           for (int i = 0; i < 4; ++i)
           {
           int step { m_players[m_current_turn].get_piece(i).currentStep };
           if (step != -1 || step != 56)
           {
           if (step + m_dice_roll <= 56)
           isItOrNot = true;
           }
           }

           return isItOrNot;
           */

        bool is_valid()
        { 
            if (m_dice_roll == 6 || m_dice_roll == 1)
            { 
                for (int i = 0; i < 4; ++i)
                { 
                    int step { m_players[m_current_turn].get_piece(i).currentStep };
                    if (step == -1) return true;
                }
            }

            for (int i = 0; i < 4; ++i)
            { 
                int step { m_players[m_current_turn].get_piece(i).currentStep };
                if (step != -1 && step != 56)
                { 
                    if ((step + m_dice_roll) <= 56) 
                        return true;
                }
            }
            return false;
        }

        bool check_finished(int move_piece_idx)
        { 
            if (m_players[m_current_turn].get_piece(move_piece_idx).currentStep == 56)
                return true;

            return false;
        }

        bool check_capture(int moved_piece_idx)
        { 
            Vector2 landed_at { m_players[m_current_turn].getPieceGridPos(moved_piece_idx) };

            if (is_tile_safe(landed_at))
                return false;

            bool is_captured { false };
            for (int p = 0; p < 4; ++p)
            { 
                if (p == m_current_turn)
                    continue;

                for (int i = 0; i < 4; ++i)
                { 
                    Vector2 oppPos { m_players[p].getPieceGridPos(i) };
                    if (oppPos.x == landed_at.x && oppPos.y == landed_at.y)
                    { 
                        m_players[p].reset_piece(i);
                        is_captured = true;
                    }
                }
            }

            return is_captured;
        }

        void handle_click(Vector2 mouse_pos)
        { 
            if (!m_has_rolled) return;

            int grid_x { static_cast<int>(mouse_pos.x) / g_size };
            int grid_y { static_cast<int>(mouse_pos.y) / g_size };

            if (m_dice_roll == 6 || m_dice_roll == 1)
            { 
                if (is_yard(m_current_turn, Vector2{static_cast<float>(grid_x), 
                            static_cast<float>(grid_y)}))
                { 
                    for (int i = 0; i < 4; ++i)
                    { 
                        if (m_players[m_current_turn].get_piece(i).currentStep == -1)
                        { 
                            m_players[m_current_turn].move_piece(i, 1);
                            resolve_turn(false, false);
                            return;
                        }
                    }
                }
            }

            int piece_idx { m_players[m_current_turn].get_piece_at(grid_x, grid_y) };
            if (piece_idx != -1)
            { 
                if (m_players[m_current_turn].move_piece(piece_idx, m_dice_roll))
                { 
                    bool is_finished = check_finished(piece_idx);
                    bool isKilled = check_capture(piece_idx);
                    resolve_turn(isKilled, is_finished);
                }
            }
        }

        void draw_game()
        { 
            draw_board();
            for (int p = 0; p < 4; ++p)
            { 
                m_players[p].draw_pieces(g_size);
            }
            draw_dice(m_dice_roll, { 7 * g_size, 7 * g_size }, g_size * 0.75f);
        }

        void process_input()
        { 
            bool input_detected {};
            Vector2 input_pos {};

#if defined(MOBILE)
            if (GetTouchPointCount() > 0)
            { 
                input_pos = GetTouchPosition(0);

                if (IsGestureDetected(GESTURE_TAP))
                    input_detected = true;
            }
#else
            if (IsKeyPressed(KEY_SPACE) && !m_has_rolled)
                roll_dice();

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            { 
                input_pos = GetMousePosition();
                input_detected = true;
            }
#endif

            if (input_detected)
            { 
                int grid_x {
                    static_cast<int>(input_pos.x) / g_size
                };
                int grid_y {
                    static_cast<int>(input_pos.y) / g_size
                };

                if (grid_x >= 6 && grid_x <= 8
                        && 
                        grid_y >= 6 && grid_y <= 8)
                { 
                    roll_dice();
                }
                else if (m_has_rolled)
                { 
                    handle_click(input_pos);
                }
            }

            update_game_logic();
        }
};

#endif
