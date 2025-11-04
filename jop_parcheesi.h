#pragma once
#include "iparcheesi.h"

class jop_parcheesi : public IParcheesi {
public:
    static const int kSafePoints = 12;
    static const int kMaxPlayers = 4;
    static const int kTotalBoxes = 68+1;

    struct Piece{
        Color color;
        int piece_index;
        int box_num, turn, player_index;
    };

    struct Player{
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
    // cada jugador tiene 8 casillas de pasillo
    static const int kLaneSize = 8;

    // Start of private exit lane for player
    // amarillo, azul, rojo, verde
    const int kLaneStart[kMaxPlayers] = {
        69,   // amarillo
        77,   // azul
        85,   // rojo
        93    // verde
    };

    Box Boxes[kTotalBoxes];

    //Ctr for the Boxes array.
    jop_parcheesi();

    int CountPiecesOnBox(int box) const;

    const int kSafePoint[kSafePoints] = {5, 12, 17, 22, 29, 34, 39, 46, 51, 56, 63, 68};
    const int kStartPoint[kMaxPlayers] = {5, 22, 39, 56};
    const int kFinishPoint[kMaxPlayers] = {68, 17, 34, 51};

    int EntryBox(int player_index) const override;
    int ExitBox(int player_index) const override;
    int PiecesAtHome(int player_index) const override;
    int PiecesAtEnd(int player_index) const override;
    bool IsBoxSafe(int box_index) const override;
    bool IsBridge(int box_index) const;
    // higher box_piece_index means the piece moved later
    Color ColorofPiece(int box_index, int box_piece_index) const override;
    // Added so the player bot can know the pieces position
    int PiecePosition(int player_index, int piece_index) const;
    bool IsInLane(Piece piece, int player_index) const;
    int LaneEnd(int player_index) const;

    Movement ApplyMovement(int piece_index, int player_index, int count) override;
    void SendPieceHome(int piece_index, int player_index) override;


    IParcheesi* Clone() const override;
    ~jop_parcheesi() = default;

    Player players[kMaxPlayers];
    
protected:
    bool HasAnyLegalMove(int player_index, int count) const;
    int* ListMovementBoxes(int start, int count, int player_index) const;
    mutable int boxlist[20];
    bool CanMove(int start, int count, int player_index) const;

};