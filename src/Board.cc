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
      switch(board.Get(i, j)) {
        case WHITE_PAWN:
          os << "  P  |";
          break;

        case BLACK_PAWN:
          os << " *P* |";
          break;

        case WHITE_KNIGHT:
          os << "  N  |";
          break;

        case BLACK_KNIGHT:
          os << " *N* |";
          break;


        case WHITE_BISHOP:
          os << "  B  |";
          break;

        case BLACK_BISHOP:
          os << " *B* |";
          break;

        case WHITE_ROOK:
          os << "  R  |";
          break;

        case BLACK_ROOK:
          os << " *R* |";
          break;


        case WHITE_QUEEN:
          os << "  Q  |";
          break;

        case BLACK_QUEEN:
          os << " *Q* |";
          break;


        case WHITE_KING:
          os << "  K  |";
          break;

        case BLACK_KING:
          os << " *K* |";
          break;

        case NIL:
          os << "     |";
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
}
