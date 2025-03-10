#include "../include/evaluate.h"
#include "../include/types.h"

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

char	init_pst(t_pst *table)
{
	short	pawn[64] = {0, 0, 0, 0, 0, 0, 0, 0, \
						50, 50, 50, 50, 50, 50, 50, 50, \
						10, 10, 20, 30, 30, 20, 10, 10, \
						5, 5, 10, 25, 25, 10, 5, 5, \
						0, 0, 0, 20, 20, 0, 0, 0, \
						5, -5, -10, 0, 0, -10, -5, 5, \
						5, 10, 10, -20, -20, 10, 10, 5, \
						0, 0, 0, 0, 0, 0, 0, 0};
	table->pawn = malloc(sizeof(short) * 64);
	if (!table->pawn)
		return (-1);
	for (int i = 0; i < 64; i++)
		table->pawn[i] = pawn[i];

	short	knight[64] = {-50, -40, -30, -30, -30, -30, -40, -50, \
						  -40, -20, 0, 0, 0, 0, -20, -40, \
						  -30, 0, 10, 15, 15, 10, 0, -30, \
						  -30, 5, 15, 20, 20, 15, 5, -30, \
						  -30, 0, 15, 20, 20, 15, 0, -30, \
						  -30, 5, 10, 15, 15, 10, 5, -30, \
						  -40, -20, 0, 5, 5, 0, -20, -40, \
						  -50, -40, -30, -30, -30, -30, -40, -50};
	table->knight = malloc(sizeof(short) * 64);
	if (!table->knight)
		return (-1);
	for (int i = 0; i < 64; i++)
		table->knight[i] = knight[i];

	short	bishop[64] = {-20, -10, -10, -10, -10, -10, -10, -20, \
						  -10, 0, 0, 0, 0, 0, 0, -10, \
						  -10, 0, 5, 10, 10, 5, 0, -10, \
						  -10, 5, 5, 10, 10, 5, 5, -10, \
						  -10, 0, 10, 10, 10, 10, 0, -10, \
						  -10, 10, 10, 10, 10, 10, 10, -10, \
						  -10, 5, 0, 0, 0, 0, 5, -10, \
						  -20, -10, -10, -10, -10, -10, -10, -20};
	table->bishop = malloc(sizeof(short) * 64);
	if (!table->bishop)
		return (-1);
	for (int i = 0; i < 64; i++)
		table->bishop[i] = bishop[i];

	short	rook[64] = {0, 0, 0, 0, 0, 0, 0, 0, \
						5, 10, 10, 10, 10, 10, 10, 5, \
						-5, 0, 0, 0, 0, 0, 0, -5, \
						-5, 0, 0, 0, 0, 0, 0, -5, \
						-5, 0, 0, 0, 0, 0, 0, -5, \
						-5, 0, 0, 0, 0, 0, 0, -5, \
						-5, 0, 0, 0, 0, 0, 0, -5, \
						0, 0, 0, 5, 5, 0, 0, 0};
	table->rook = malloc(sizeof(short) * 64);
	if (!table->rook)
		return (-1);
	for (int i = 0; i < 64; i++)
		table->rook[i] = rook[i];

	short	queen[64] = {-20, -10, -10, -5, -5, -10, -10, -20, \
						 -10, 0, 0, 0, 0, 0, 0, -10, \
						 -10, 0, 5, 5, 5, 5, 0, -10, \
						 -5, 0, 5, 5, 5, 5, 0, -5, \
						  0, 0, 5, 5, 5, 5, 0, 0, \
						 -10, 5, 5, 5, 5, 5, 5, -10, \
						 -10, 0, 5, 0, 0, 5, 0, -10, \
						 -20, -10, -10, -5, -5, -10, -10, -20};
	table->queen = malloc(sizeof(short) * 64);
	if (!table->queen)
		return (-1);
	for (int i = 0; i < 64; i++)
		table->queen[i] = queen[i];

	short	king[64] = {-30, -40, -40, -50, -50, -40, -40, -30, \
						-30, -40, -40, -50, -50, -40, -40, -30, \
						-30, -40, -40, -50, -50, -40, -40, -30, \
						-30, -40, -40, -50, -50, -40, -40, -30, \
						-20, -30, -30, -40, -40, -30, -30, -20, \
						-10, -20, -20, -20, -20, -20, -20, -10, \
						 20, 20, 0, 0, 0, 0, 20, 20, \
						 20, 30, 10, 0, 0, 10, 30, 20};
	table->king = malloc(sizeof(short) * 64);
	if (!table->king)
		return (-1);
	for (int i = 0; i < 64; i++)
		table->king[i] = king[i];
	return (0);
}

int	main(void)
{
	t_pst table;
	if (init_pst(&table) == -1)
		return (-1);
	for (int i = 0; i < 64; i++)
	{
		printf("[%d]:%d\t", i, table.pawn[i]);
		if (((i + 1) % 8) == 0)
			printf("\n");
	}
}
