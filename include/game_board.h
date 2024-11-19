/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-11-19 12:54:24
 */

#pragma once

#include "common.h"

enum TileElement
{
    TileElement_Empty,
    TileElement_X,
    TileElement_O
};

struct Game_Board
{
public:
    Game_Board();
    ~Game_Board() = default;

    void DisplayMap();
    
    bool CheckWinCondition(TileElement Element);
    bool Tie();
    bool IsValidPosition(i32 X, i32 Y);

    i32 Minimax(bool IsMaximizing, i32 Depth);
    void BestMoveAI();

    void Set(i32 X, i32 Y, TileElement Element)
    {
        Map[X][Y] = Element;
    }
private:
    TileElement Map[3][3];
};
