#include <stdio.h>
#include "../include/bitboards.h"
#include "../include/types.h"

void	print_bitboard(long board)
{
	for (int rank = 0; rank < 8; rank++)
	{
		for (int file = 7; file >= 0; file--)
		{
			long mask = (long)1 << (63 - (rank * 8) - file);
			printf("%d ", (board & mask) != 0 ? 1 : 0);
		}
		printf("\n");
	}
}

void	init_bitboards(t_bitboards *bb)
{
	int			i;
	const long	one = 1;

	bb->side[C_WHITE] = 0;
	for (i = 0; i < 16; i++)
		bb->side[C_WHITE] |= (one << i);

	bb->side[C_BLACK] = 0;
	for (i = 63; i > 47; i--)
		bb->side[C_BLACK] |= (one << i);

	bb->pieces[C_WHITE][BP_KING] = 0;
	bb->pieces[C_WHITE][BP_KING] |= (one << 4);
	bb->pieces[C_BLACK][BP_KING] = 0;
	bb->pieces[C_BLACK][BP_KING] |= (one << 60);

	bb->pieces[C_WHITE][BP_QUEEN] = 0;
	bb->pieces[C_WHITE][BP_QUEEN] |= (one << 3);
	bb->pieces[C_BLACK][BP_QUEEN] = 0;
	bb->pieces[C_BLACK][BP_QUEEN] |= (one << 59);

	bb->pieces[C_WHITE][BP_ROOK] = 0;
	bb->pieces[C_WHITE][BP_ROOK] |= (one << 7);
	bb->pieces[C_WHITE][BP_ROOK] |= (one << 0);
	bb->pieces[C_BLACK][BP_ROOK] = 0;
	bb->pieces[C_BLACK][BP_ROOK] |= (one << 63);
	bb->pieces[C_BLACK][BP_ROOK] |= (one << 56);

	bb->pieces[C_WHITE][BP_BISHOP] = 0;
	bb->pieces[C_WHITE][BP_BISHOP] |= (one << 5);
	bb->pieces[C_WHITE][BP_BISHOP] |= (one << 2);
	bb->pieces[C_BLACK][BP_BISHOP] = 0;
	bb->pieces[C_BLACK][BP_BISHOP] |= (one << 61);
	bb->pieces[C_BLACK][BP_BISHOP] |= (one << 58);

	bb->pieces[C_WHITE][BP_KNIGHT] = 0;
	bb->pieces[C_WHITE][BP_KNIGHT] |= (one << 6);
	bb->pieces[C_WHITE][BP_KNIGHT] |= (one << 1);
	bb->pieces[C_BLACK][BP_KNIGHT] = 0;
	bb->pieces[C_BLACK][BP_KNIGHT] |= (one << 62);
	bb->pieces[C_BLACK][BP_KNIGHT] |= (one << 57);

	bb->pieces[C_WHITE][BP_PAWN] = 0;
	for (i = 8; i < 16; i++)
		bb->pieces[C_WHITE][BP_PAWN] |= (one << i);

	bb->pieces[C_BLACK][BP_PAWN] = 0;
	for (i = 55; i > 47; i--)
		bb->pieces[C_BLACK][BP_PAWN] |= (one << i);
}

int	main(void)
{
	t_bitboards bb;
	init_bitboards(&bb);
	printf("--------------WHITES\n");
	print_bitboard(bb.side[C_WHITE]);
	printf("KING\n");
	print_bitboard(bb.pieces[C_WHITE][BP_KING]);
	printf("QUEEN\n");
	print_bitboard(bb.pieces[C_WHITE][BP_QUEEN]);
	printf("ROOK\n");
	print_bitboard(bb.pieces[C_WHITE][BP_ROOK]);
	printf("BISHOP\n");
	print_bitboard(bb.pieces[C_WHITE][BP_BISHOP]);
	printf("KNIGHT\n");
	print_bitboard(bb.pieces[C_WHITE][BP_KNIGHT]);
	printf("PAWN\n");
	print_bitboard(bb.pieces[C_WHITE][BP_PAWN]);

	printf("--------------BLACKS\n");
	print_bitboard(bb.side[C_BLACK]);
	printf("KING\n");
	print_bitboard(bb.pieces[C_BLACK][BP_KING]);
	printf("QUEEN\n");
	print_bitboard(bb.pieces[C_BLACK][BP_QUEEN]);
	printf("ROOK\n");
	print_bitboard(bb.pieces[C_BLACK][BP_ROOK]);
	printf("BISHOP\n");
	print_bitboard(bb.pieces[C_BLACK][BP_BISHOP]);
	printf("KNIGHT\n");
	print_bitboard(bb.pieces[C_BLACK][BP_KNIGHT]);
	printf("PAWN\n");
	print_bitboard(bb.pieces[C_BLACK][BP_PAWN]);
}
