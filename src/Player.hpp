#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Constants.hpp"
#include "Draw.hpp"
#include <raylib.h>
#include <math.h>
// 0 is red, 1 Green, 2 is Yellow, 3 is Blue

struct Piece
{ 
    int currentStep {};
    bool isFinished {};
    int owner_id {};
    int pieceId {};
};

class Player 
{ 
    private:
        Piece m_piece[4];
        Color m_color{};
        bool is_my_turn{};
        int m_player_id{};

    public:
        Player(int id)
            : m_player_id { id }
        { 
            m_color = colors[id];
            for (int i = 0; i < 4; ++i)
            {
                m_piece[i].currentStep = -1;
                m_piece[i].isFinished = false;
                m_piece[i].pieceId = i;
                m_piece[i].owner_id = id;
            }
        }

        bool is_winner()
        { 
            int final_count {};
            for (int i = 0; i < 4; ++i)
            { 
                if (m_piece[i].isFinished)
                    ++final_count;
            }

            return (final_count == 4);
        }

        Vector2 getPieceGridPos(int piece_id)
        { 
            int step { get_piece(piece_id).currentStep };
            if (step == -1) return { -1, -1 };

            if (step < 51) { 
                int actual_steps { (m_player_id * 13 + step) % 52 };
                return global_path[actual_steps];
            }

            int home_idx { step - 51 };

            if (home_idx > 5)
                home_idx = 5;

            return homeStretch[m_player_id][home_idx];
        }

        int get_piece_at(int x, int y)
        { 
            for (int i = 0; i < 4; ++i)
            { 
                if (m_piece[i].currentStep == -1) continue; // Just skip the locked pieces

                Vector2 pos { getPieceGridPos(i) };
                if (static_cast<int>(pos.x) == x && static_cast<int>(pos.y) == y)
                { 
                    return i;
                }
            }

            return -1;
        }

        void move_piece(int piece_id, int dice_roll)
        { 
            if (piece_id < 0 || piece_id > 3) return;
            Piece& p { m_piece[piece_id] };
            if (p.currentStep == -1)
            { 
                p.currentStep = 0; 
            }

            else if (!p.isFinished)
            { 
                if (p.currentStep + dice_roll <= 56)
                { 
                    p.currentStep += dice_roll;
                }

                if (p.currentStep == 56)
                {
                    p.isFinished = true;
                }
            }
        }

        void draw_pieces(int cellSize)
        { 
            for (int i = 0; i < 4; ++i)
            { 
                Vector2 gridPos{};
                float jumpY = 0.0f;

                if (m_piece[i].currentStep == -1)
                { 
                    Vector2 yardOffset = home_offset[m_player_id];
                    gridPos = { yardOffset.x + 1.0f + (i % 2) * 3.0f, yardOffset.y + 1.0f + (i/2) * 3.0f };
                }
                else 
                { 
                    gridPos = getPieceGridPos(i);
                }

                if (is_my_turn)
                { 
                    jumpY = fabsf(sinf(GetTime() * 8.0f)) * 15.0f;
                }

                Vector2 screen_pos { 
                    (gridPos.x * cellSize) + cellSize / 2.0f,
                        (gridPos.y * cellSize) + cellSize / 2.0f
                };

                draw_ludo_pawn(screen_pos, m_color, jumpY);
            }
        }

        void reset_piece(int idx) { m_piece[idx].currentStep = -1; }
        const Piece& get_piece(int idx) const { return m_piece[idx]; }
        void set_turn(bool turn) { is_my_turn = turn; }
        const bool isMyTurn() const { return is_my_turn; }
};

#endif
