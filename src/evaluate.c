#include "../include/evaluate.h"
#include "../include/types.h"
#include <stdlib.h>

static const int piece_value[6] = { 100, 300, 300, 500, 900, 1000000 };

int evaluate(const struct position *pos) {
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

int	init_pst(t_pst *table)
{
	int i;
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
	table->pawn = malloc(sizeof(short) * 64);
	table->knight = malloc(sizeof(short) * 64);
	table->bishop = malloc(sizeof(short) * 64);
	table->rook = malloc(sizeof(short) * 64);
	table->queen = malloc(sizeof(short) * 64);
	table->king = malloc(sizeof(short) * 64);
	if (!table->pawn || !table->knight || !table->bishop
		|| !table->rook || !table->queen || !table->king)
		return (free(table->pawn), free(table->knight), free(table->bishop),
				free(table->rook), free(table->queen), free(table->king), -1);
	for (i = 0; i < 64; i++)
	{
		table->pawn[i] = pawntable[i];
		table->knight[i] = knighttable[i];
		table->bishop[i] = bishoptable[i];
		table->rook[i] = rooktable[i];
		table->queen[i] = queentable[i];
		table->king[i] = kingtable[i];
	}
	return (0);
}

/*int	main(void)
{
	t_pst table;
	int i;
	if (init_pst(&table) == -1)
		return (-1);
	for (i = 0; i < 64; i++)
	{
		printf("[%d]:%d\t", i, table.pawn[i]);
		if (((i + 1) % 8) == 0)
			printf("\n");
	}
}*/
