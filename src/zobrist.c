#include <stdlib.h>
#include "../include/zobrist.h"
#include "../include/bitboards.h"

void	init_board(t_board *board);

long random_long() {
	unsigned int lower = rand();
	unsigned int upper = rand();
	long random_number = ((long)upper << 32) | lower;
	return ((long)((long)upper << 32) | lower); // can never have enough casts babyy
}

void fill_zobrist_hashes(zob_hashes *hashes)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 64; k++)
				hashes->piece_hashes[i][j][k] = random_long();
		}
	}
	for (int i = 0; i < 16; i++)
		hashes->castling_hashes[i] = random_long();
	for (int i = 0; i < 17; i++)
		hashes->en_passant_hashes[i] = random_long();
	hashes->side_hashes[0] = random_long();
	hashes->side_hashes[1] = random_long();
}

int nextbit(long *bitboard)
{
	if (*bitboard == 0)
		return (-1);
	int bit = *bitboard & 1;
	*bitboard >>= 1;
	return (bit);
}

long init_gamestate(zob_hashes *hashes, t_board *board, t_gamestate *state)
{
	long gskey = 0;
	t_board nboard = *board;
	zob_hashes nhashes = *hashes;
	long *wpieces = board->pieces[C_WHITE];
	long *bpieces = board->pieces[C_BLACK];
	for (int i = 0; i < 6; i++)
	{
		long whitepiece = wpieces[i];
		long blackpiece = bpieces[i];
		while (whitepiece > 0)
		{
			int square = nextbit(&whitepiece);
			gskey ^= nhashes.piece_hashes[C_WHITE][nboard.piece_list[square]][square];
		}
		while (blackpiece > 0)
		{
			int square = nextbit(&blackpiece);
			gskey ^= nhashes.piece_hashes[C_BLACK][nboard.piece_list[square]][square];
		}
	}
	gskey ^= nhashes.castling_hashes[state->castling];
	gskey ^= nhashes.side_hashes[state->active_color];
	gskey ^= nhashes.en_passant_hashes[state->active_color];
	return (gskey);
}

void	print_piecelist(int *list);
void	init_piece_list(t_board *board);

int main() {
	t_board board;
	zob_hashes hashes;
	t_gamestate state;
	init_board(&board);
	init_piece_list(&board);
	fill_zobrist_hashes(&hashes);
	init_gamestate(&hashes, &board, &state);
	print_piecelist(board.piece_list);
    return 0;
}