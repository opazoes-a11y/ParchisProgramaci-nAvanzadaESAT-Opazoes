#pragma once
#include "iparcheesi.h"

class jop_parcheesi : public IParcheesi {
public:
    static const int kSafePoints = 12;
    static const int kMaxPlayers = 4;
    static const int kTotalBoxes = 68+1;

    static struct Piece{
        Color color;
        int piece_index;
        int box_num, turn, player_index;
    };

    static struct Player{
        int player_index;
        Color color;
        Piece player_pieces[pieces_per_player];
    };

    class Box{
        public:
        int piecesIn;
        int boxIndex;
        bool isBridge;
        bool isSafe;

        Box();
        Box(int index);
    };

    Box Boxes[kTotalBoxes];

    //Ctr for the Boxes array.
    jop_parcheesi();

    const int kSafePoint[kSafePoints] = {5, 12, 17, 22, 29, 34, 39, 46, 51, 56, 63, 68};
    const int kStartPoint[kMaxPlayers] = {5, 22, 39, 56};
    const int kFinishPoint[kMaxPlayers] = {68, 17, 34, 51};

    int EntryBox(int player_index) const override;
    int ExitBox(int player_index) const override;
    int PiecesAtHome(int player_index) const override;
    int PiecesAtEnd(int player_index) const override;
    bool IsBoxSafe(int box_index) const override;
    // higher box_piece_index means the piece moved later
    Color ColorofPiece(int box_index, int box_piece_index) const override;

    Movement ApplyMovement(int piece_index, int player_index, int count) override;
    void SendPieceHome(int piece_index, int player_index) override;

    IParcheesi* Clone() const override;
    ~jop_parcheesi() = default;

protected:
    Player players[kMaxPlayers];
};