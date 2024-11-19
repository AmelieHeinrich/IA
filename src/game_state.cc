/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-11-19 12:52:41
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <utility>

#include "game_state.h"

Game_State::Game_State()
    : Board()
{
}

void Game_State::Run()
{
    bool GameWon = false;
    bool CurrentTurn = false; // false for p1, true for p2
    while (!GameWon)
    {
        Board.DisplayMap();

        /// @NOTE(amélie): Query input
        if (CurrentTurn == false)
        {
            i32 X = 4, Y = 4;
            while (!Board.IsValidPosition(X, Y))
            {
                printf("Choose position for O (Format: X Y): ");
                scanf("%d %d", &X, &Y);
            }
            Board.Set(X, Y, TileElement_O);
        }
        else
        {
            printf("AI is thinking...\n");
            Board.BestMoveAI();
        }
        CurrentTurn = !CurrentTurn;

        bool P1Won = Board.CheckWinCondition(TileElement_O);
        bool P2Won = Board.CheckWinCondition(TileElement_X);
        bool Tied = Board.Tie();
        GameWon = P1Won || P2Won || Tied;

        if (P1Won)
        {
            Board.DisplayMap();
            printf("Victory for O!\n");
        }
        else if (P2Won)
        {
            Board.DisplayMap();
            printf("Victory for X!\n");
        }
        else if (Tied)
        {
            Board.DisplayMap();
            printf("Tie!");
        }
    }
}
