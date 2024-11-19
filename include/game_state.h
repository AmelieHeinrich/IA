/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-11-19 12:51:51
 */

#pragma once

#include "common.h"
#include "game_board.h"

struct Game_State
{
public:
    Game_State();
    ~Game_State() = default;

    void Run();
private:
    Game_Board Board;
};
