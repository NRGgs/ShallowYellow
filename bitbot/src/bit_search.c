#include "../include/bitboards.h"

#define MAX_MOVES 256

struct search_result minimax(t_board *board, int depth) {

	if (depth == 0) {
		result.score = evaluate(pos);
	} else {
		t_move moves[MAX_MOVES];
		size_t count = generate_legal_moves(pos, moves);
		size_t index;

		for (index = 0; index < count; index++) {
			// struct position copy = *pos;
			int score;

			do_move(&copy, moves[index]);

			score = -minimax(&copy, depth - 1).score;

			if (score > result.score) {
				result.move = moves[index];
				result.score = score;
			}
		}
	}

	return result;
}

t_move search(const struct search_info *info) {
	return minimax(boards, 4).move;
}
