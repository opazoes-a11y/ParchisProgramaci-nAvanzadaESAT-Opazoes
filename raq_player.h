#include "iparcheesi.h"
#include "game.h"


class RaqPlayer : public IPlayer{
  virtual int DecideMove(const IParcheesi& parcheesi, int current_player_index, int dice_roll) const override;
};