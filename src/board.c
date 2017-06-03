#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct board * get_new_board()
{
	struct board *b = malloc(sizeof(struct board));
	if (!b) {
		return NULL;
	}
	memset(b, 0, sizeof(struct board));
	memset(b->board, NIL, sizeof(b->board));

	b->board[A1] = b->board[H1] = WHITE_ROOK;
	b->board[B1] = b->board[G1] = WHITE_KNIGHT;
	b->board[C1] = b->board[F1] = WHITE_BISHOP;
	b->board[D1] = WHITE_QUEEN;
	b->board[E1] = WHITE_KING;

	b->board[A2] = b->board[B2] = b->board[C2] = b->board[D2] = WHITE_PAWN;
	b->board[E2] = b->board[F2] = b->board[G2] = b->board[H2] = WHITE_PAWN;

	b->board[A8] = b->board[H8] = BLACK_ROOK;
	b->board[B8] = b->board[G8] = BLACK_KNIGHT;
	b->board[C8] = b->board[F8] = BLACK_BISHOP;
	b->board[D8] = BLACK_QUEEN;
	b->board[E8] = BLACK_KING;

	b->board[A7] = b->board[B7] = b->board[C7] = b->board[D7] = BLACK_PAWN;
	b->board[E7] = b->board[F7] = b->board[G7] = b->board[H7] = BLACK_PAWN;

	return b;
}

inline const enum piece_info board_get_from_indices(
		struct board *board, unsigned char i, unsigned char j)
{
	const enum square_index index = (i << 4) + j;
	return board_get_from_index(board, index);
}

inline const enum piece_info board_get_from_index(
		struct board *b, enum square_index index)
{
	if (index & 0x88)
		return NIL;
	return b->board[index];
}

static const char *piece_str(enum piece_info info) {
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

void board_print(struct board *b)
{
	printf("### board ###\n");
	printf("#\n");
	printf("#----------------------------------------------------\n");

	/* Put black on top and white on bottom */
	for (char i = 7; i >= 0; --i) {
		printf("# %d |", i);
		for (char j = 0; j < 8; ++j) {
			enum piece_info info = board_get_from_indices(b, i, j);
			printf(" %s |", piece_str(info));
		}
		printf("\n");
		printf("#----------------------------------------------------\n");
	}
	printf("#      a     b     c     d     e     f     g     h\n");
	printf("#\n");
	fflush(stdout);
}
