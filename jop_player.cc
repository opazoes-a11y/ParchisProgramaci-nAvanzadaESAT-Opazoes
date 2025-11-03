#include "jop_player.h"
#include <memory>

int Player::DecideMove(const IParcheesi& parchis, int player_index, int dice_roll) const {
    const int base = player_index * IParcheesi::pieces_per_player;

    // Mandatory exit rule: if we rolled 5 and we have pieces at home,
    // we must try to bring one out.
    if (dice_roll == 5 && parchis.PiecesAtHome(player_index) > 0) {
        // Try each of our 4 pieces, but only the ones that are actually at home.
        for (int local_p = 0; local_p < IParcheesi::pieces_per_player; ++local_p) {
            int pos = parchis.PiecePosition(player_index, local_p);
            if (pos != 0)
                continue; // not at home

            int global_p = base + local_p;

            // Simulate on a clone to see if the entry is blocked
            std::unique_ptr<IParcheesi> sim(parchis.Clone());
            IParcheesi::Movement r = sim->ApplyMovement(global_p, player_index, dice_roll);

            // If the entry is blocked or any other illegal, try next home piece
            if (r >= IParcheesi::Movement::IllegalPass) {
                continue;
            }

            // This home piece can really enter, so we choose it
            return global_p;
        }

        // If we are here, we rolled 5, we have pieces at home,
        // but none of them could actually enter (bridge or enemy on safe).
        return base;
    }

    // try all 4 pieces, simulate, and keep the best legal ones.
    struct Candidate {
        int piece_global = -1;
        IParcheesi::Movement result = IParcheesi::Movement::NoMoves;
    };

    Candidate best_eat;
    Candidate best_end;
    Candidate first_legal;

    for (int local_p = 0; local_p < IParcheesi::pieces_per_player; ++local_p) {
        int global_p = base + local_p;

        std::unique_ptr<IParcheesi> sim(parchis.Clone());
        IParcheesi::Movement r = sim->ApplyMovement(global_p, player_index, dice_roll);

        // Skip illegal moves (blocked by bridge, entry blocked, past end...)
        if (r >= IParcheesi::Movement::IllegalPass)
            continue;

        // First legal move we find
        if (first_legal.piece_global == -1) {
            first_legal.piece_global = global_p;
            first_legal.result = r;
        }

        // Prefer eat
        if (r == IParcheesi::Movement::Eat) {
            best_eat.piece_global = global_p;
            best_eat.result = r;
        }

        // Prefer reaching the end
        if (r == IParcheesi::Movement::End) {
            best_end.piece_global = global_p;
            best_end.result = r;
        }
    }

    // Priority order
    if (best_eat.piece_global != -1)
        return best_eat.piece_global;

    if (best_end.piece_global != -1)
        return best_end.piece_global;

    if (first_legal.piece_global != -1)
        return first_legal.piece_global;

    // If nothing was legal, let the board return NoMoves
    return base;
}
