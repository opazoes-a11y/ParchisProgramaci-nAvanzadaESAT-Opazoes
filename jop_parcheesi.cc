#include "jop_parcheesi.h"

jop_parcheesi::Box::Box() : piecesIn(0), boxIndex(-1), isBridge(false), isSafe(false) {}

jop_parcheesi::Box::Box(int index) : piecesIn(0), boxIndex(index), isBridge(false), isSafe(false) {}

jop_parcheesi::jop_parcheesi(){
    for (int i = 0; i < kTotalBoxes; ++i) {
        Boxes[i] = Box(i);
        Boxes[i].isSafe = IsBoxSafe(i);
    }
    players[0].color = IParcheesi::Color::Yellow;
    for(int i=0; i<pieces_per_player; ++i){
        players[0].player_pieces[i].color =IParcheesi::Color::Yellow;
        players[0].player_pieces[i].player_index = 0;
        //Boxnum=0 para casa
        players[0].player_pieces[i].box_num = 0;
        players[0].player_pieces[i].piece_index = i;
    }
    players[1].color = IParcheesi::Color::Blue;
    for(int i=0; i<pieces_per_player; ++i){
        players[1].player_pieces[i].color =IParcheesi::Color::Blue;
        players[1].player_pieces[i].player_index = 1;
        players[1].player_pieces[i].box_num = 0;
        players[1].player_pieces[i].piece_index = i+4;
    }
    players[2].color = IParcheesi::Color::Red;
    for(int i=0; i<pieces_per_player; ++i){
        players[2].player_pieces[i].color =IParcheesi::Color::Red;
        players[2].player_pieces[i].player_index = 2;
        players[2].player_pieces[i].box_num = 0;
        players[2].player_pieces[i].piece_index = i+8;
    }
    players[3].color = IParcheesi::Color::Green;
    for(int i=0; i<pieces_per_player; ++i){
        players[3].player_pieces[i].color =IParcheesi::Color::Green;
        players[3].player_pieces[i].player_index = 3;
        players[3].player_pieces[i].box_num = 0;
        players[3].player_pieces[i].piece_index = i+12;
    }
}

int jop_parcheesi::EntryBox(int player_index) const{
    return kStartPoint[player_index];
}

int jop_parcheesi::ExitBox(int player_index) const{
    return kFinishPoint[player_index];
}

int jop_parcheesi::PiecesAtHome(int player_index) const{
    int HowManyAtHome = 0;
    for(int i=0; IParcheesi::pieces_per_player; ++i){
        if(players[player_index].player_pieces[i].box_num == 0){
            HowManyAtHome++;
        }
    }
    return HowManyAtHome;
}

int jop_parcheesi::PiecesAtEnd(int player_index) const{
    int HowManyAtGoal = 0;
    for(int i=0; IParcheesi::pieces_per_player; ++i){
        if(players[player_index].player_pieces[i].box_num == ExitBox(player_index)){
            HowManyAtGoal++;
        }
    }
    return HowManyAtGoal;
}

bool jop_parcheesi::IsBoxSafe(int box_index) const{
    for(int i=0; i<jop_parcheesi::kSafePoints; ++i){
        if(box_index == kSafePoint[i]){
            return true;
        }
    }
    return false;
}

jop_parcheesi::Color jop_parcheesi::ColorofPiece(int box_index, int box_piece_index) const{
    for(int i, j=0; i<kMaxPlayers, j<pieces_per_player; ++i, ++j){
        if(players[i].player_pieces[j].box_num==box_index) return players[i].player_pieces[j].color;
    }
    return IParcheesi::Color::None;
}

IParcheesi::Movement jop_parcheesi::ApplyMovement(int piece_index, int player_index, int count) {
    Piece* moving_piece = nullptr;
    for (int i = 0; i < pieces_per_player; ++i) {
        if (players[player_index].player_pieces[i].piece_index == piece_index) {
            moving_piece = &players[player_index].player_pieces[i];
            break;
        }
    }
    if (!moving_piece) return Movement::NoMoves;

    int current_box = moving_piece->box_num;

    // home == box 0
    if (current_box == 0) {
        if (count != 5)
            return Movement::IllegalPieceAtHome; // Only if rolled a 5

        int entry = kStartPoint[player_index];
        int same_color_count = 0;
        bool rival_here = false;
        int rival_player = -1, rival_piece = -1;

        // Check who's on the exit box
        for (int pl = 0; pl < kMaxPlayers; ++pl) {
            for (int p = 0; p < pieces_per_player; ++p) {
                const Piece& piece = players[pl].player_pieces[p];
                if (piece.box_num == entry) {
                    if (pl == player_index) same_color_count++;
                    else {
                        rival_here = true;
                        rival_player = pl;
                        rival_piece = p;
                    }
                }
            }
        }

        // Bridges
        if (same_color_count >= 2)
            return Movement::IllegalBridge;

        // Check if there's a rival in safe box
        if (rival_here && IsBoxSafe(entry))
            return Movement::IllegalEntryBlocked;

        // Eat rival if posisioned in no safe box
        if (rival_here && !IsBoxSafe(entry)) {
            players[rival_player].player_pieces[rival_piece].box_num = 0;
            moving_piece->box_num = entry;
            Boxes[entry].piecesIn = 1;
            return Movement::Eat;
        }

        // No rivals on target box
        moving_piece->box_num = entry;
        Boxes[entry].piecesIn++;
        return Movement::Normal;
    }

    // If piece is already in the board
    int destination = current_box + count;

    if (destination > IParcheesi::board_size)
        destination = ((destination - 1) % IParcheesi::board_size) + 1;

    // Check if reached exit box
    if (destination == kFinishPoint[player_index])
        return Movement::ReachExit;

    // Check moving box
    int same_color_count = 0;
    bool rival_here = false;
    int rival_player = -1, rival_piece = -1;

    for (int pl = 0; pl < kMaxPlayers; ++pl) {
        for (int p = 0; p < pieces_per_player; ++p) {
            const Piece& piece = players[pl].player_pieces[p];
            if (piece.box_num == destination) {
                if (pl == player_index) same_color_count++;
                else {
                    rival_here = true;
                    rival_player = pl;
                    rival_piece = p;
                }
            }
        }
    }

    // Check for bridges -> illegal move
    if (same_color_count >= 2)
        return Movement::IllegalBridge;

    // Rival in safe box -> bloqued movement
    if (rival_here && IsBoxSafe(destination))
        return Movement::IllegalEntryBlocked;

    // Rival in normal box -> eat
    if (rival_here && !IsBoxSafe(destination)) {
        players[rival_player].player_pieces[rival_piece].box_num = 0; // rival a casa
        moving_piece->box_num = destination;
        Boxes[destination].piecesIn = 1;
        return Movement::Eat;
    }

    // Normal move
    Boxes[current_box].piecesIn--;
    moving_piece->box_num = destination;
    Boxes[destination].piecesIn++;
    return Movement::Normal;
}


void jop_parcheesi::SendPieceHome(int piece_index, int player_index){
    for(int i=0; i<pieces_per_player; i++){
        if(players[player_index].player_pieces[i].piece_index==piece_index){
            players[player_index].player_pieces[i].box_num==0;
        }
    }
}
