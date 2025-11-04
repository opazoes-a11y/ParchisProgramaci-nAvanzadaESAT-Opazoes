#include <windows.h>
#include "game.h"
#include "jop_parcheesi.h"
#include "jop_player.h"
#include "raq_player.h"
#include "playerElena.h"
#include "gsh_player.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    jop_parcheesi board;

    static Player p0;
    static PlayerElena p1;
    static GPlayer p2;
    static RaqPlayer p3;

    const IPlayer* players[4] = { &p0, &p1, &p2, &p3 };

    Game g{ board, players };

    while (g.IsGameOver() == IParcheesi::Color::None) {
        g.PlayTurn();
        Sleep(100);
    }

    return 0;
}