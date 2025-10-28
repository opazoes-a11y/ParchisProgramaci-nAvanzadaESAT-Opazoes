
enum PieceColor {
  kPC_Yellow,
  kPC_Blue,
  kPC_Red,
  kPC_Green,
  kPC_None,
};

class IParcheesi {
  public:
    enum MovementType {
      kMT_Eat,
      kMT_End,
      kMT_Reach_Exit,
      kMT_Normal,
      kMT_No_Moves,
      kMT_Illegal_Pass,
      kMT_Illegal_Bridge,
      kMT_Illegal_Box_Full,
      kMT_Illegal_Past_End,
      kMT_Illegal_Entry_Blocked,
      kMT_Illegal_Piece_At_Home,
      kMT_Illegal_Must_Enter_Piece,
      kMT_Illegal_Must_Break_Bridge,
    };

    const static int board_size = 68;
    const static int exit_size = 8;
    const static int null_piece = -1;

    virtual int EntryBox(int player_index) const = 0;
    virtual int ExitBox(int player_index) const = 0;
    virtual int PiecesAtHome(int player_index) const = 0;
    virtual int PiecesAtEnd(int player_index) const = 0;
    virtual PieceColor ColorofPiece(int box_index, int piece_index) const = 0;
    virtual bool IsBoxSafe(int box_index) const = 0;

    virtual MovementType ApplyMovement(int piece_index, int count) = 0;
};


class MyParcheesi : public IParcheesi {

    virtual int EntryBox(int player_index) const ;
    virtual int ExitBox(int player_index) const;
    virtual int PiecesAtHome(int player_index) const;
    virtual int PiecesAtEnd(int player_index) const;
    virtual PieceColor ColorofPiece(int box_index, int piece_index) const;
    virtual bool IsBoxSafe(int box_index) const;

    virtual MovementType ApplyMovement(int piece_index, int count);
};
int DecideMovement(int player,int roll, const IParcheesi& board);

class Game {
  IParcheesi& p_;
  public:
    Game(IParcheesi& p) : p_{p} {}

    PlayTurn() {
      p_.ExitBox();
    }
    Roll();
    IsGameOver();
    ActivePlayer();

};

int main(){
  MyParcheesi myp;
  Game g{myp};

  while(g.IsGameOver() == kPC_None) {
    g.Turn();
  }
}

