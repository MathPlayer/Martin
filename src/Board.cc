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

static const char *piece_str(enum PieceInfo info) {
  return (info == NIL)      ? "   " :
    (info == WHITE_KING)    ? " K " : // " \u2654 "
    (info == WHITE_QUEEN)   ? " Q " : // " \u2655 "
    (info == WHITE_ROOK)    ? " R " : // " \u2656 "
    (info == WHITE_BISHOP)  ? " B " : // " \u2657 "
    (info == WHITE_KNIGHT)  ? " N " : // " \u2658 "
    (info == WHITE_PAWN)    ? " P " : // " \u2659 "
    (info == BLACK_KING)    ? "*K*" : // " \u265A "
    (info == BLACK_QUEEN)   ? "*Q*" : // " \u265B "
    (info == BLACK_ROOK)    ? "*R*" : // " \u265C "
    (info == BLACK_BISHOP)  ? "*B*" : // " \u265D "
    (info == BLACK_KNIGHT)  ? "*N*" : // " \u265E "
    (info == BLACK_PAWN)    ? "*P*" : // " \u265F "
    "?????";
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
      os << " " << piece_str(info) << " |";
    }
    os << std::endl
      << "#----------------------------------------------------"
      << std::endl;
  }
  os << "#      a     b     c     d     e     f     g     h" << std::endl;
  os << "#" << std::endl;

  return os;
}
