#pragma once
#ifndef JOP_PLAYER_H
#define JOP_PLAYER_H
#include "game.h"

class Player : public IPlayer {
public:
    int DecideMove(const IParcheesi& parchis, int player_index, int dice_roll) const override;
};
#endif