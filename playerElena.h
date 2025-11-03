#pragma once
#ifndef PLAYERELENA_H
#define PLAYERELENA_H

#include "game.h"

class PlayerElena : public IPlayer {
  public:
    virtual int DecideMove(const IParcheesi& parcheesi, int player_index, int dice_roll) const;
};

#endif //PLAYERELENA_H