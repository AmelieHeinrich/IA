/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-11-18 15:19:22
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

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
    {
        i32 WinCounter = 0;
        if (Map[0][0] == Element)
            WinCounter++;
        if (Map[1][1] == Element)
            WinCounter++;
        if (Map[2][2] == Element)
            WinCounter++;
        if (WinCounter == 3)
            return true;
    }

    return false;
}

bool IsValidPosition(i32 X, i32 Y, TileElement Map[3][3])
{
    return (X >= 0 && X < 3 && Y >= 0 && Y < 3 && Map[X][Y] == TileElement_Empty);
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
            i32 X = 4, Y = 4;
            while (!IsValidPosition(X, Y, Map))
            {
                printf("Choose position for X (Format: X Y): ");
                scanf("%d %d", &X, &Y);
            }
            Map[X][Y] = TileElement_X;
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
