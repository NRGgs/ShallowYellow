#include "../include/search.h"
#include "../include/evaluate.h"
#include "../include/generate.h"
#include "../include/types.h"

#include <limits.h>

int *evaluate(const struct position *pos, struct move move, int **table, int total_value[2]);

struct search_result minimax(const struct position *pos, const struct position *og, struct move *move, int depth, int **table,
							int alpha, int beta, int total_value[2]) {
	struct search_result result;
	int valuecpy[2];
	valuecpy[0] = total_value[0];
	valuecpy[1] = total_value[1];
	int is_maxing = depth % 2;

	result.score = (is_maxing) ? -1000000 : 1000000;

	if (depth == 0) {
		/* we have reached our search depth, so evaluate the position.       */
		evaluate(og, *move, table, valuecpy);
		result.score = valuecpy[pos->side_to_move] - valuecpy[1 - pos->side_to_move];
	} else {
		struct move moves[MAX_MOVES];
		size_t count = generate_legal_moves(pos, moves);
		size_t index;

		for (index = 0; index < count; index++) {
			struct position copy = *pos;
			int score;

			/* do a move, the current player in `copy` is then the opponent, */
			/* and so when we call minimax we get the score of the opponent. */
			do_move(&copy, moves[index]);

			/* minimax is called recursively. this call returns the score of */
			/* the opponent, so we must negate it to get our score.          */
			score = minimax(&copy, pos, &moves[index], depth - 1, table, alpha, beta, valuecpy).score;

			/* update the best move if we found a better one.                */
			if (is_maxing) {
				if (score > result.score)
				{
					result.move = moves[index];
					result.score = score;
				}
				alpha = (score > alpha) ? score : alpha;
			}
			else {
				if (score < result.score)
				{
					result.move = moves[index];
					result.score = score;
				}
				beta = (score < beta) ? score : beta;
			}
			if (alpha >= beta)
				break;
		}
	}
	// printf("----------%d----------\n", result.score);
	// printf("-----beta: %d -----alpha: %d -----\n\n", beta, alpha);
	return result;
}

struct move search(const struct search_info *info, int **table) {
	int	alpha = INT_MIN;
	int	beta = INT_MAX;

	int score[2] = { 0, 0 };
	static const int piece_value[6] = { 100, 300, 300, 500, 900, 25565 };
	int square;
	for (square = 0; square < 64; square++) {
		int piece = info->pos->board[square];

		if (piece != NO_PIECE) {
			score[COLOR(piece)] += (piece_value[TYPE(piece)] + table[TYPE(piece)][RELATIVESQUARE(square, piece)]);
		}
	}
	printf("-----score: %d-----\n\n\n", score[info->pos->side_to_move] - score[1 - info->pos->side_to_move]);
	// return minimax(info->pos, NULL, NULL, 8, table, alpha, beta, score).move;
	struct search_result result = minimax(info->pos, NULL, NULL, 5, table, alpha, beta, score);
	printf("----------%d----------\n\n", result.score);
	return (result.move);
}
