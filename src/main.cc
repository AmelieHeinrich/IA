/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-11-18 15:19:22
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <utility>

#include "common.h"

enum TileElement
{
    TileElement_Empty,
    TileElement_X,
    TileElement_O
};

void DisplayMap(TileElement Map[3][3])
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

bool CheckWinCondition(TileElement Map[3][3], TileElement Element)
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

bool IsValidPosition(i32 X, i32 Y, TileElement Map[3][3])
{
    return (X >= 0 && X < 3 && Y >= 0 && Y < 3 && Map[X][Y] == TileElement_Empty);
}

i32 Minimax(TileElement Map[3][3], bool IsMaximizing, i32 Depth)
{
    if (CheckWinCondition(Map, TileElement_X))
    {
        return 10 - Depth;
    }
    if (CheckWinCondition(Map, TileElement_O))
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
                    Best = std::max(Best, Minimax(Map, false, Depth + 1));
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
                    Best = std::min(Best, Minimax(Map, true, Depth + 1));
                    Map[X][Y] = TileElement_Empty;
                }
            }
        }
        return Best;
    }
}

void BestMove(TileElement Map[3][3])
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
                i32 MoveVal = Minimax(Map, false, 0);
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

i32 main(void)
{
    TileElement Map[3][3];
    memset(Map, TileElement_Empty, sizeof(TileElement) * 3 * 3);

    bool GameWon = false;
    bool CurrentTurn = false; // false for p1, true for p2
    while (!GameWon)
    {
        DisplayMap(Map);

        /// @NOTE(amélie): Query input
        if (CurrentTurn == false)
        {
            i32 X = 4, Y = 4;
            while (!IsValidPosition(X, Y, Map))
            {
                printf("Choose position for O (Format: X Y): ");
                scanf("%d %d", &X, &Y);
            }
            Map[X][Y] = TileElement_O;
        }
        else
        {
            printf("AI is thinking...");
            BestMove(Map);
        }
        CurrentTurn = !CurrentTurn;

        bool P1Won = CheckWinCondition(Map, TileElement_O);
        bool P2Won = CheckWinCondition(Map, TileElement_X);
        GameWon = P1Won || P2Won;

        if (P1Won)
        {
            DisplayMap(Map);
            printf("Victory for O!\n");
        }
        else if (P2Won)
        {
            DisplayMap(Map);
            printf("Victory for X!\n");
        }
    }

    return 0;
}
