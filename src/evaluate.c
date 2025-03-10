#include "../include/evaluate.h"
#include "../include/types.h"
#include "../include/position.h"
#include <stdlib.h>

static const int piece_value[6] = { 100, 300, 300, 500, 900, 1000000 };

int evaluate(const struct position *pos, short **table) {
	int score[2] = { 0, 0 };
	int square;

	for (square = 0; square < 64; square++) {
		int piece = pos->board[square];

		if (piece != NO_PIECE) {
			score[COLOR(piece)] += (piece_value[TYPE(piece)] + table[TYPE(piece)][square]);
		}
	}

	return score[pos->side_to_move] - score[1 - pos->side_to_move];
}

int old_evaluate(const struct position *pos) {
	int score[2] = { 0, 0 };
	int square;

	for (square = 0; square < 64; square++) {
		int piece = pos->board[square];

		if (piece != NO_PIECE) {
			score[COLOR(piece)] += piece_value[TYPE(piece)];
		}
	}

	return score[pos->side_to_move] - score[1 - pos->side_to_move];
}

int	init_pst(short ***table)
{
	short i;
	short	pawntable[64] = {0, 0, 0, 0, 0, 0, 0, 0,
						50, 50, 50, 50, 50, 50, 50, 50,
						10, 10, 20, 30, 30, 20, 10, 10,
						5, 5, 10, 25, 25, 10, 5, 5,
						0, 0, 0, 20, 20, 0, 0, 0,
						5, -5, -10, 0, 0, -10, -5, 5,
						5, 10, 10, -20, -20, 10, 10, 5,
						0, 0, 0, 0, 0, 0, 0, 0};
	short	knighttable[64] = {-50, -40, -30, -30, -30, -30, -40, -50,
						-40, -20, 0, 0, 0, 0, -20, -40,
						-30, 0, 10, 15, 15, 10, 0, -30,
						-30, 5, 15, 20, 20, 15, 5, -30,
						-30, 0, 15, 20, 20, 15, 0, -30,
						-30, 5, 10, 15, 15, 10, 5, -30,
						-40, -20, 0, 5, 5, 0, -20, -40,
						-50, -40, -30, -30, -30, -30, -40, -50};
	short	bishoptable[64] = {-20, -10, -10, -10, -10, -10, -10, -20,
						  -10, 0, 0, 0, 0, 0, 0, -10,
						  -10, 0, 5, 10, 10, 5, 0, -10,
						  -10, 5, 5, 10, 10, 5, 5, -10,
						  -10, 0, 10, 10, 10, 10, 0, -10,
						  -10, 10, 10, 10, 10, 10, 10, -10,
						  -10, 5, 0, 0, 0, 0, 5, -10,
						  -20, -10, -10, -10, -10, -10, -10, -20};
	short	rooktable[64] = {0, 0, 0, 0, 0, 0, 0, 0,
						5, 10, 10, 10, 10, 10, 10, 5,
						-5, 0, 0, 0, 0, 0, 0, -5,
						-5, 0, 0, 0, 0, 0, 0, -5,
						-5, 0, 0, 0, 0, 0, 0, -5,
						-5, 0, 0, 0, 0, 0, 0, -5,
						-5, 0, 0, 0, 0, 0, 0, -5,
						0, 0, 0, 5, 5, 0, 0, 0};
	short	queentable[64] = {-20, -10, -10, -5, -5, -10, -10, -20,
						 -10, 0, 0, 0, 0, 0, 0, -10,
						 -10, 0, 5, 5, 5, 5, 0, -10,
						 -5, 0, 5, 5, 5, 5, 0, -5,
						  0, 0, 5, 5, 5, 5, 0, 0,
						 -10, 5, 5, 5, 5, 5, 5, -10,
						 -10, 0, 5, 0, 0, 5, 0, -10,
						 -20, -10, -10, -5, -5, -10, -10, -20};
	short	kingtable[64] = {-30, -40, -40, -50, -50, -40, -40, -30,
						-30, -40, -40, -50, -50, -40, -40, -30,
						-30, -40, -40, -50, -50, -40, -40, -30,
						-30, -40, -40, -50, -50, -40, -40, -30,
						-20, -30, -30, -40, -40, -30, -30, -20,
						-10, -20, -20, -20, -20, -20, -20, -10,
						 20, 20, 0, 0, 0, 0, 20, 20,
						 20, 30, 10, 0, 0, 10, 30, 20};
	*table = malloc(sizeof(short *) * 6);
	(*table)[PAWN] = malloc(sizeof(short) * 64);
	(*table)[KNIGHT] = malloc(sizeof(short) * 64);
	(*table)[BISHOP] = malloc(sizeof(short) * 64);
	(*table)[ROOK] = malloc(sizeof(short) * 64);
	(*table)[QUEEN] = malloc(sizeof(short) * 64);
	(*table)[KING] = malloc(sizeof(short) * 64);
	for (i = 0; i < 6; i++)
		if (!(*table)[i])
			return (free((*table)[PAWN]), free((*table)[KNIGHT]), free((*table)[BISHOP]),
				free((*table)[ROOK]), free((*table)[QUEEN]), free((*table)[KING]), -1);
	for (i = 0; i < 64; i++)
	{
		(*table)[PAWN][i] = pawntable[i];
		(*table)[KNIGHT][i] = knighttable[i];
		(*table)[BISHOP][i] = bishoptable[i];
		(*table)[ROOK][i] = rooktable[i];
		(*table)[QUEEN][i] = queentable[i];
		(*table)[KING][i] = kingtable[i];
	}
	return (0);
}

int	main(void)
{
	short **table;
	struct position pos;
	int i;
	if (init_pst(&table) == -1)
		return (-1);
	parse_position(&pos, "rnb2k1r/1ppp2p1/p3pn1p/4N3/3P1P2/1N4P1/P1Q1K2P/R4B1R b - - 0 17");
	print_position(&pos, stdout);
	printf("Score for this position: %d\n", evaluate(&pos, table));
	printf("OLD Score for this position: %d\n", old_evaluate(&pos));
	for (i = 0; i < 6; i++) {
		free(table[i]);
	}
	free(table);
}
