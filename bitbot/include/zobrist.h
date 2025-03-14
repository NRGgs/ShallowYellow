#ifndef ZOBRIST_H
#define ZOBRIST_H


void fill_zobrist_hashes(zob_hashes *hashes);
unsigned long get_starting_game_hash(zob_hashes *hashes, t_board *board);


#endif