#pragma once
#ifndef GSHPLAYER_H
#define GSHPLAYER_H

#include "iparcheesi.h"
#include "game.h"


class GPlayer : public IPlayer {
public:

    virtual int DecideMove(const IParcheesi& parcheesi, int current_player_index, int dice_roll) const override;
    int PriorityOfMovement(IParcheesi::Movement mov) const;

};

#endif // PLAYER_H