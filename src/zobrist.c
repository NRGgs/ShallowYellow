#include <stdlib.h>
#include "../include/zobrist.h"
#include "../include/bitboards.h"
#include "../include/gamestate.h"

void	init_board(t_board *board);

unsigned long random_long() {
	unsigned int lower = rand();
	unsigned int upper = rand();
	unsigned long random_number = ((unsigned long)upper << 32) | lower;
	return ((unsigned long)((unsigned long)upper << 32) | lower); // can never have enough casts babyy
}

void fill_zobrist_hashes(zob_hashes *hashes)
{
	unsigned long last = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 64; k++)
			{
				hashes->piece_hashes[i][j][k] = random_long();
				if (last == hashes->piece_hashes[i][j][k])
					printf("Duplicate hash found %ld\n", last);
				last = hashes->piece_hashes[i][j][k];
			}
		}
	}
	for (int i = 0; i < 16; i++)
		hashes->castling_hashes[i] = random_long();
	for (int i = 0; i < 17; i++)
		hashes->en_passant_hashes[i] = random_long();
	hashes->side_hashes[0] = random_long();
	hashes->side_hashes[1] = random_long();
}

int nextbit(unsigned long *bitboard)
{
	if (*bitboard == 0)
		return (-1);
	unsigned long bit = *bitboard & (unsigned long)1;
	*bitboard >>= (unsigned long)1;
	return (bit);
}

unsigned long get_starting_game_hash(zob_hashes *hashes, t_board *board, t_gamestate *state)
{
	unsigned long gskey = 0;
	t_board nboard = *board;
	zob_hashes nhashes = *hashes;
	unsigned long *wpieces = board->pieces[C_WHITE];
	unsigned long *bpieces = board->pieces[C_BLACK];
	for (int i = 0; i < 6; i++)
	{
		unsigned long whitepiece = wpieces[i];
		unsigned long blackpiece = bpieces[i];
		int square = 0;
		while (whitepiece > 0)
		{
			int type = nboard.piece_list[square];
			gskey ^= nhashes.piece_hashes[C_WHITE][type][square];
			nextbit(&whitepiece);
			square++;
		}
		square = 0;
		while (blackpiece > 0)
		{
			int type = nboard.piece_list[square];
			gskey ^= nhashes.piece_hashes[C_BLACK][type][square];
			nextbit(&blackpiece);
			square++;
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
	print_piecelist(board.piece_list);
	state.zobrist_key = get_starting_game_hash(&hashes, &board, &state);
	printf("%ld\n", state.zobrist_key);
    return 0;
}