#include "Board.h"

#include <cstring>

Board::Board()
{
  memset(board, NIL, sizeof(board));

  board[A1] = board[H1] = WHITE_ROOK;
  board[B1] = board[G1] = WHITE_KNIGHT;
  board[C1] = board[F1] = WHITE_BISHOP;
  board[D1] = WHITE_QUEEN;
  board[E1] = WHITE_KING;

  board[A2] = board[B2] = board[C2] = board[D2] = WHITE_PAWN;
  board[E2] = board[F2] = board[G2] = board[H2] = WHITE_PAWN;

  board[A8] = board[H8] = BLACK_ROOK;
  board[B8] = board[G8] = BLACK_KNIGHT;
  board[C8] = board[F8] = BLACK_BISHOP;
  board[D8] = BLACK_QUEEN;
  board[E8] = BLACK_KING;

  board[A7] = board[B7] = board[C7] = board[D7] = BLACK_PAWN;
  board[E7] = board[F7] = board[G7] = board[H7] = BLACK_PAWN;
}

inline enum PieceInfo Board::Get(unsigned char i, unsigned char j) const
{
  return Get(static_cast<enum SquareIndex>((i << 4) + j));
}

inline enum PieceInfo Board::Get(enum SquareIndex index) const
{
  if (index & 0x88)
    return NIL;
  return this->board[index];
}

static const char *print_pieces[] = {
  [NIL]          = "   ",
#ifdef _WIN32
  [WHITE_KING]   = " K ",
  [WHITE_QUEEN]  = " Q ",
  [WHITE_ROOK]   = " R ",
  [WHITE_BISHOP] = " B ",
  [WHITE_KNIGHT] = " N ",
  [WHITE_PAWN]   = " P ",
  [BLACK_KING]   = "*K*",
  [BLACK_QUEEN]  = "*Q*",
  [BLACK_ROOK]   = "*R*",
  [BLACK_BISHOP] = "*B*",
  [BLACK_KNIGHT] = "*N*",
  [BLACK_PAWN]   = "*P*",
#else
  [WHITE_KING]   = " \u2654 ",
  [WHITE_QUEEN]  = " \u2655 ",
  [WHITE_ROOK]   = " \u2656 ",
  [WHITE_BISHOP] = " \u2657 ",
  [WHITE_KNIGHT] = " \u2658 ",
  [WHITE_PAWN]   = " \u2659 ",
  [BLACK_KING]   = " \u265A ",
  [BLACK_QUEEN]  = " \u265B ",
  [BLACK_ROOK]   = " \u265C ",
  [BLACK_BISHOP] = " \u265D ",
  [BLACK_KNIGHT] = " \u265E ",
  [BLACK_PAWN]   = " \u265F ",
#endif
};

std::ostream& operator<<(std::ostream& os, const Board &board)
{
  os << "### board ###" << std::endl
    << "#" << std::endl
    << "#----------------------------------------------------"
    << std::endl;

  // Put black on top and white on bottom
  for (char i = 7; i >= 0; --i) {
    os << "# " << static_cast<short>(i) << " |";
    for (char j = 0; j < 8; ++j) {
      enum PieceInfo info = board.Get(i, j);
      switch(info) {
        case WHITE_PAWN:
        case BLACK_PAWN:
        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
        case WHITE_BISHOP:
        case BLACK_BISHOP:
        case WHITE_ROOK:
        case BLACK_ROOK:
        case WHITE_QUEEN:
        case BLACK_QUEEN:
        case WHITE_KING:
        case BLACK_KING:
        case NIL:
          os << " " << print_pieces[info] << " |";
          break;

        default:
          os << " ??? |";
          break;
      }
    }
    os << std::endl
      << "#----------------------------------------------------"
      << std::endl;
  }
  os << "#      a     b     c     d     e     f     g     h" << std::endl;
  os << "#" << std::endl;

  return os;
}
