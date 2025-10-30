#pragma once
#include "iparcheesi.h"
#include "jop_parcheesi.h"

class jop_player : public IParcheesi{
    int player_index;
    Color color;
    jop_parcheesi::Player player_pieces[pieces_per_player];
};