/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-11-19 12:56:39
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <utility>

#include "common.h"
#include "game_board.h"

Game_Board::Game_Board()
{
    memset(Map, TileElement_Empty, sizeof(TileElement) * 3 * 3);
}

void Game_Board::DisplayMap()
{
    for (i32 X = 0; X < 3; X++)
    {
        for (i32 Y = 0; Y < 3; Y++)
        {
            switch (Map[X][Y])
            {
                case TileElement_Empty:
                    printf("-");
                    break;
                case TileElement_X:
                    printf("X");
                    break;
                case TileElement_O:
                    printf("O");
                    break;
            }
        }
        printf("\n");
    }
}

bool Game_Board::CheckWinCondition(TileElement Element)
{
    // @NOTE(amélie): Check for rows
    for (i32 X = 0; X < 3; X++)
    {
        i32 WinCounter = 0;
        if (Map[X][0] == Element)
            WinCounter++;
        if (Map[X][1] == Element)
            WinCounter++;
        if (Map[X][2] == Element)
            WinCounter++;
        if (WinCounter == 3)
            return true;
    }

    // @NOTE(amélie): Check for columns
    for (i32 Y = 0; Y < 3; Y++)
    {
        i32 WinCounter = 0;
        if (Map[0][Y] == Element)
            WinCounter++;
        if (Map[1][Y] == Element)
            WinCounter++;
        if (Map[2][Y] == Element)
            WinCounter++;
        if (WinCounter == 3)
            return true;
    }

    // @NOTE(amélie): Check for diagonals
    if ((Map[0][0] == Element && Map[1][1] == Element && Map[2][2] == Element)
     || (Map[0][2] == Element && Map[1][1] == Element && Map[2][0] == Element))
    {
         return true;
    }

    return false;
}

bool Game_Board::IsValidPosition(i32 X, i32 Y)
{
    return (X >= 0 && X < 3 && Y >= 0 && Y < 3 && Map[X][Y] == TileElement_Empty);
}

i32 Game_Board::Minimax(bool IsMaximizing, i32 Depth)
{
    if (CheckWinCondition(TileElement_X))
    {
        return 10 - Depth;
    }
    if (CheckWinCondition(TileElement_O))
    {
        return Depth - 10;
    }
    
    bool IsFull = true;
    for (i32 X = 0; X < 3; X++)
    {
        for (i32 Y = 0; Y < 3; Y++)
        {
            if (Map[X][Y] == TileElement_Empty)
            {
                IsFull = false;
            }
        }
    }
    if (IsFull)
        return 0;  // Draw

    if (IsMaximizing)
    {
        i32 Best = -INT_MAX;
        for (i32 X = 0; X < 3; X++)
        {
            for (i32 Y = 0; Y < 3; Y++)
            {
                if (Map[X][Y] == TileElement_Empty)
                {
                    Map[X][Y] = TileElement_X;
                    Best = std::max(Best, Minimax(false, Depth + 1));
                    Map[X][Y] = TileElement_Empty;
                }
            }
        }
        return Best;
    }
    else
    {
        i32 Best = INT_MAX;
        for (i32 X = 0; X < 3; X++)
        {
            for (i32 Y = 0; Y < 3; Y++)
            {
                if (Map[X][Y] == TileElement_Empty)
                {
                    Map[X][Y] = TileElement_O;
                    Best = std::min(Best, Minimax(true, Depth + 1));
                    Map[X][Y] = TileElement_Empty;
                }
            }
        }
        return Best;
    }
}

void Game_Board::BestMoveAI()
{
    i32 BestVal = -INT_MAX;
    i32 BestX = -1, BestY = -1;

    for (i32 X = 0; X < 3; X++)
    {
        for (i32 Y = 0; Y < 3; Y++)
        {
            if (Map[X][Y] == TileElement_Empty)
            {
                Map[X][Y] = TileElement_X;
                i32 MoveVal = Minimax(false, 0);
                Map[X][Y] = TileElement_Empty;
                if (MoveVal > BestVal)
                {
                    BestX = X;
                    BestY = Y;
                    BestVal =MoveVal;
                }
            }
        }
    }

    Map[BestX][BestY] = TileElement_X;
}

bool Game_Board::Tie()
{
    for (i32 X = 0; X < 3; X++)
    {
        for (i32 Y = 0; Y < 3; Y++)
        {
            if (Map[X][Y] == TileElement_Empty)
            {
                return false;
            }
        }
    }
    return true;
}
