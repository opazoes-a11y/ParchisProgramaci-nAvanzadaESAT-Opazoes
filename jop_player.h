#pragma once
#include "game.h"

class Player : public IPlayer {
public:
    int DecideMove(const IParcheesi& parchis, int player_index, int dice_roll) const override;
};
