#include "search.h"
#include "evaluate.h"
#include "generate.h"

#include <limits.h>

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

struct search_result minimax(const struct position *pos, int depth, int ***table, bool max_player, int alpha, int beta) {
	struct search_result result;

	size_t i;

	if (depth == 0) {
		result.score = evaluate(pos, table);
	} else {
		struct move moves[MAX_MOVES];
		size_t count = generate_legal_moves(pos, moves);
		int score;

		if (max_player)
		{
			result.score = INT_MIN;
			for (i = 0; i < count; i++)
			{
				struct position copy = *pos;
				do_move(&copy, moves[i]);
				score = minimax(&copy, depth - 1, table, false, alpha, beta).score;
				if (score > result.score)
				{
					result.score = score;
					result.move = moves[i];
				}
				alpha = max(alpha, score);
				if (beta <= alpha)
					break;
			}
			return result;
		}
		else
		{
			result.score = INT_MAX;
			for (i = 0; i < count; i++)
			{
				struct position copy = *pos;
				do_move(&copy, moves[i]);
				score = minimax(&copy, depth - 1, table, true, alpha, beta).score;
				if (score < result.score)
				{
					result.score = score;
					result.move = moves[i];
				}
				beta = min(beta, score);
				if (beta <= alpha)
					break;
			}
			return result;
		}
	}
	return result;
}

struct move search(const struct search_info *info, int ***table) {
	return minimax(info->pos, 6, table, true, INT_MIN, INT_MAX).move;
}
