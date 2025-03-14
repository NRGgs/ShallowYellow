#include "../include/move.h"
#include "../include/types.h"
#include "../include/bitboards.h"
#include "../include/zobrist.h"
#include "../include/evaluate.h"

void	print_piecelist(int *list);
void	bbdo_move(t_board *board, struct move move);
void	print_bitboard(long board);


int main(void)
{
	t_board board;
	zob_hashes hashes;
	init_board(&board);
	init_piece_list(&board);
	fill_zobrist_hashes(&hashes);
	board.state.zobrist_key = get_starting_game_hash(&hashes, &board);
	board.hashes = &hashes;
	init_pst(&board.table);



	struct move test;
	test.from_square = 8;
	test.to_square = 24;
	test.promotion_type = NO_PIECE;
	bbdo_move(&board, test);
	print_piecelist(board.piece_list);
	printf("\n");
	print_bitboard(board.pieces[C_WHITE][BP_PAWN]);

	add_history(&board);

	test.from_square = 49;
	test.to_square = 33;
	test.promotion_type = NO_PIECE;
	bbdo_move(&board, test);
	printf("\n");
	print_piecelist(board.piece_list);
	printf("\n");
	print_bitboard(board.pieces[C_BLACK][BP_PAWN]);

	add_history(&board);

	test.from_square = 24;
	test.to_square = 33;
	test.promotion_type = NO_PIECE;
	bbdo_move(&board, test);
	print_piecelist(board.piece_list);
	printf("\n");
	print_bitboard(board.pieces[C_WHITE][BP_PAWN]);

	add_history(&board);

	printf("----BLACK PAWN AND BOARD\n");
	print_bitboard(board.pieces[C_BLACK][BP_PAWN]);
	printf("\n");
	print_bitboard(board.side[C_BLACK]);

	printf("-----UNDO\n");
	undo_state(&board);
	print_piecelist(board.piece_list);
	printf("\n");
	print_bitboard(board.pieces[C_WHITE][BP_PAWN]);

	add_history(&board);

	printf("----BLACK PAWN AND BOARD\n");
	print_bitboard(board.pieces[C_BLACK][BP_PAWN]);
	printf("\n");
	print_bitboard(board.side[C_BLACK]);

	printf("----WHITE PAWN AND BOARD\n");
	print_bitboard(board.pieces[C_WHITE][BP_PAWN]);
	printf("\n");
	print_bitboard(board.side[C_WHITE]);

}

void remove_piece(t_board *board, int color, int piece, int square)
{
	board->pieces[color][piece] ^= ((long)1 << square);
	board->side[color] ^= ((long)1 << square);
	board->piece_list[square] = BP_NONE;
	board->state.zobrist_key ^= board->hashes->piece_hashes[color][piece][square];

	board->state.score_value -= 0; // remove piece value
	printf("square: %d - %d\n", square, BB_RELATIVESQUARE(square, color));
	board->state.ps_value[color] -= board->table[piece][0][BB_RELATIVESQUARE(square, color)];
}

void place_piece(t_board *board, int color, int piece, int square)
{
	int target = board->piece_list[square];
	if (target != BP_NONE)
	{
		board->pieces[color ^ 1][target] &= ~((long)1 << square);
		board->side[color ^ 1] &= ~((long)1 << square);
	}

	board->pieces[color][piece] |= ((long)1 << square);
	board->side[color] |= ((long)1 << square);
	board->piece_list[square] = piece;
	board->state.zobrist_key ^= board->hashes->piece_hashes[color][piece][square];

	board->state.score_value += 0; // remove piece value
	printf("square: %d - %d\n", square, BB_RELATIVESQUARE(square, color));
	printf("piece: %d\n", piece);
	board->state.ps_value[color] += board->table[piece][0][BB_RELATIVESQUARE(square, color)];
}

void	set_enpassant(t_board *board, int color, int square)
{
	int ep_square = square == -1 ? 16 : GET_ENPASSANT_SQUARE(color, board->state.en_passant);
	board->state.zobrist_key ^= board->hashes->en_passant_hashes[ep_square];
	board->state.en_passant = square;
	board->state.zobrist_key ^= board->hashes->en_passant_hashes[GET_ENPASSANT_SQUARE(color, board->state.en_passant)];
}

void	clear_enpassant(t_board *board, int color)
{
	board->state.zobrist_key ^= board->hashes->en_passant_hashes[GET_ENPASSANT_SQUARE(color, board->state.en_passant)];
	board->state.en_passant = -1;
	board->state.zobrist_key ^= board->hashes->en_passant_hashes[16];
}

void	swap_side(t_board *board)
{
	board->state.zobrist_key ^= board->hashes->side_hashes[board->state.active_color];
	board->state.active_color ^= 1;
	board->state.zobrist_key ^= board->hashes->side_hashes[board->state.active_color];
}

// void	update_castling(t_board *board, int new_castling)
// {
// 	board->state.zobrist_key ^= board->hashes->castling_hashes[board->state.castling];
// 	board->state.castling = new_castling;
// 	board->state.zobrist_key ^= board->hashes->side_hashes[board->state.castling];
// }

int jehovah(int old)
{
	switch (old)
	{
		case PAWN: return BP_PAWN;
		case KNIGHT: return BP_KNIGHT;
		case BISHOP: return BP_BISHOP;
		case ROOK: return BP_ROOK;
		case QUEEN: return BP_QUEEN;
		case KING: return BP_KING;
		default: return BP_NONE;
	}
}

void	bbdo_move(t_board *board, struct move move)
{
	int from_file = FILE(move.from_square);
	int from_rank = RANK(move.from_square);
	int to_file = FILE(move.to_square);
	int to_rank = RANK(move.to_square);
	int piece = board->piece_list[move.from_square];
	int color = board->state.active_color;
	int a1 = SQUARE(FILE_A, RELATIVE(RANK_1, color));
	int h1 = SQUARE(FILE_H, RELATIVE(RANK_1, color));
	int a8 = SQUARE(FILE_A, RELATIVE(RANK_8, color));
	int h8 = SQUARE(FILE_H, RELATIVE(RANK_8, color));
	int en_passant_square = board->state.en_passant;

	printf("ep: %d \
		color: %d, \
		piece: %d, \
		fromsquare: \
		%d\n", 
		en_passant_square, 
		color, 
		piece, 
		move.from_square);
	remove_piece(board, color, piece, move.from_square);
	if (move.promotion_type != NO_TYPE)
		place_piece(board, color, jehovah(move.promotion_type), move.to_square);
	else
		place_piece(board, color, piece, move.to_square);

	clear_enpassant(board, color);

	/**
	 * Pretend we castle righted!
	 */

	board->state.active_color ^= 1;
	if (piece == BP_PAWN)
	{
		if (RELATIVE(to_rank, color) - RELATIVE(from_rank, color) == 2)
			set_enpassant(board, color, (color == C_WHITE ? move.to_square - 8 : move.to_square + 8));
		if (move.to_square == en_passant_square)
			remove_piece(board, color, piece, SQUARE(to_file, from_rank));
	}
	else if (piece == BP_KING)
	{
		/**
		 * Pretend we castle righted!
		 */
	}

	board->state.completed_move = move;
}