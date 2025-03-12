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
	for (int i = 0; i < 64 * 6 * 2; i++)
		hashes->piece_hashes[i] = random_long();
	for (int i = 0; i < 16; i++)
		hashes->castling_hashes[i] = random_long();
	for (int i = 0; i < 17; i++)
		hashes->en_passant_hashes[i] = random_long();
	hashes->side_hashes[0] = random_long();
	hashes->side_hashes[1] = random_long();
}

long init_gamestate(zob_hashes *hashes, t_board *board)
{

}

int main() {
	t_board board;
	zob_hashes hashes;
	init_board(&board);
	fill_zobrist_hashes(&hashes);
	for (int i = 0; i < 64 * 6 * 2; i++)
		printf("%ld\n", hashes.piece_hashes[i]);
    return 0;
}