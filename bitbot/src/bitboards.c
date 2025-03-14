#include <stdio.h>
#include <string.h>
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

void	print_piecelist(int *list)
{
	for (int rank = 0; rank < 8; rank++)
	{
		for (int file = 7; file >= 0; file--)
		{
			printf("%d ", list[63 - (rank * 8) - file]);
		}
		printf("\n");
	}
}

void	init_board(t_board *board)
{
	int			i;
	const long	one = 1;

	board->side[C_WHITE] = 0;
	for (i = 0; i < 16; i++)
		board->side[C_WHITE] |= (one << i);

	board->side[C_BLACK] = 0;
	for (i = 63; i > 47; i--)
		board->side[C_BLACK] |= (one << i);

	board->pieces[C_WHITE][BP_KING] = 0;
	board->pieces[C_WHITE][BP_KING] |= (one << 4);
	board->pieces[C_BLACK][BP_KING] = 0;
	board->pieces[C_BLACK][BP_KING] |= (one << 60);

	board->pieces[C_WHITE][BP_QUEEN] = 0;
	board->pieces[C_WHITE][BP_QUEEN] |= (one << 3);
	board->pieces[C_BLACK][BP_QUEEN] = 0;
	board->pieces[C_BLACK][BP_QUEEN] |= (one << 59);

	board->pieces[C_WHITE][BP_ROOK] = 0;
	board->pieces[C_WHITE][BP_ROOK] |= (one << 7);
	board->pieces[C_WHITE][BP_ROOK] |= (one << 0);
	board->pieces[C_BLACK][BP_ROOK] = 0;
	board->pieces[C_BLACK][BP_ROOK] |= (one << 63);
	board->pieces[C_BLACK][BP_ROOK] |= (one << 56);

	board->pieces[C_WHITE][BP_BISHOP] = 0;
	board->pieces[C_WHITE][BP_BISHOP] |= (one << 5);
	board->pieces[C_WHITE][BP_BISHOP] |= (one << 2);
	board->pieces[C_BLACK][BP_BISHOP] = 0;
	board->pieces[C_BLACK][BP_BISHOP] |= (one << 61);
	board->pieces[C_BLACK][BP_BISHOP] |= (one << 58);

	board->pieces[C_WHITE][BP_KNIGHT] = 0;
	board->pieces[C_WHITE][BP_KNIGHT] |= (one << 6);
	board->pieces[C_WHITE][BP_KNIGHT] |= (one << 1);
	board->pieces[C_BLACK][BP_KNIGHT] = 0;
	board->pieces[C_BLACK][BP_KNIGHT] |= (one << 62);
	board->pieces[C_BLACK][BP_KNIGHT] |= (one << 57);

	board->pieces[C_WHITE][BP_PAWN] = 0;
	for (i = 8; i < 16; i++)
		board->pieces[C_WHITE][BP_PAWN] |= (one << i);
		

	board->pieces[C_BLACK][BP_PAWN] = 0;
	for (i = 55; i > 47; i--)
		board->pieces[C_BLACK][BP_PAWN] |= (one << i);
	
	board->state.active_color = 0;
	board->state.castling = 0;
	board->state.completed_move.captured_piece = BP_NONE;
	board->state.completed_move.to_square = 0;
	board->state.completed_move.from_square = 0;
	board->state.completed_move.promotion_type = BP_NONE;
	board->state.en_passant = -1;
	board->state.fullmove_number = 0;
	board->state.half_move_clock = 0;
	board->state.ps_value[0] = 0;
	board->state.ps_value[1] = 0;
	board->state.score_value = 0;
	board->history.current = 0;
}

void	init_piece_list(t_board *board)
{
	int			piece_type;
	int			square;
	const long	one = 1;

	for (int i = 0; i < 64; i++)
		board->piece_list[i] = BP_NONE;
	for (piece_type = 0; piece_type < 6; piece_type++)
	{
		for (square = 0; square < 64; square++)
		{
			board->piece_list[square] =
				((board->pieces[C_WHITE][piece_type] & (one << square)) != 0)
				? piece_type : board->piece_list[square];
			board->piece_list[square] =
				((board->pieces[C_BLACK][piece_type] & (one << square)) != 0)
				? piece_type : board->piece_list[square];
		}
	}
}

// int	main(void)
// {
// 	t_board board;
// 	init_board(&board);
// 	init_piece_list(&board);
// 	printf("--------------WHITES\n");
// 	print_bitboard(board.side[C_WHITE]);
// 	printf("KING\n");
// 	print_bitboard(board.pieces[C_WHITE][BP_KING]);
// 	printf("QUEEN\n");
// 	print_bitboard(board.pieces[C_WHITE][BP_QUEEN]);
// 	printf("ROOK\n");
// 	print_bitboard(board.pieces[C_WHITE][BP_ROOK]);
// 	printf("BISHOP\n");
// 	print_bitboard(board.pieces[C_WHITE][BP_BISHOP]);
// 	printf("KNIGHT\n");
// 	print_bitboard(board.pieces[C_WHITE][BP_KNIGHT]);
// 	printf("PAWN\n");
// 	print_bitboard(board.pieces[C_WHITE][BP_PAWN]);

// 	printf("--------------BLACKS\n");
// 	print_bitboard(board.side[C_BLACK]);
// 	printf("KING\n");
// 	print_bitboard(board.pieces[C_BLACK][BP_KING]);
// 	printf("QUEEN\n");
// 	print_bitboard(board.pieces[C_BLACK][BP_QUEEN]);
// 	printf("ROOK\n");
// 	print_bitboard(board.pieces[C_BLACK][BP_ROOK]);
// 	printf("BISHOP\n");
// 	print_bitboard(board.pieces[C_BLACK][BP_BISHOP]);
// 	printf("KNIGHT\n");
// 	print_bitboard(board.pieces[C_BLACK][BP_KNIGHT]);
// 	printf("PAWN\n");
// 	print_bitboard(board.pieces[C_BLACK][BP_PAWN]);

// 	printf("--------------PIECE_LIST\n");
// 	print_piecelist(board.piece_list);
// }
