#include "../include/evaluate.h"
#include "../include/generate.h"
#include "../include/types.h"
#include "../include/move.h"
#include <stdlib.h>

static const int piece_value[2][6] = {{ 82, 337, 365, 477, 1025, 25565 },
										{ 94, 281, 297, 512,  936, 25565 }};

void	free_this_monster(int ****table);
int		get_game_stage(const int *board);
void	center_control(const struct position *pos, int *score);
void	king_safety(const struct position *pos, int *score);
void	pawn_structure(const struct position *pos, int *score);
void	blocked_pieces(const struct position *pos, int *score);

int evaluate(const struct position *pos, int ***table)
{
	int score[2] = { 0, 0 };
	int square;
	int	game_stage = get_game_stage(pos->board);

	for (square = 0; square < 64; square++)
	{
		int piece = pos->board[square];
		int table_index = (COLOR(piece) == BLACK) ? (square ^ 56) : square;

		if (piece != NO_PIECE)
			score[COLOR(piece)] += piece_value[game_stage][TYPE(piece)] * 200 + table[TYPE(piece)][game_stage][table_index] * 100;
	}

	int	center_score[2] = {0, 0};
	center_control(pos, center_score);
	score[WHITE] += center_score[WHITE] * 10;
	score[BLACK] += center_score[BLACK] * 10;

	int king_safety_score[2] = {0, 0};
	king_safety(pos, king_safety_score);
	score[WHITE] += king_safety_score[WHITE];
	score[BLACK] += king_safety_score[BLACK];

	int pawn_structure_score[2] = {0, 0};
	pawn_structure(pos, pawn_structure_score);
	score[WHITE] += pawn_structure_score[WHITE] * 10;
	score[BLACK] += pawn_structure_score[BLACK] * 10;

	int blocked_pieces_score[2] = {0, 0};
	blocked_pieces(pos, blocked_pieces_score);
	score[WHITE] += blocked_pieces_score[WHITE] * 10;
	score[BLACK] += blocked_pieces_score[BLACK] * 10;

	return (score[pos->side_to_move] - score[1 - pos->side_to_move]);
}

void	center_control(const struct position *pos, int *score)
{
	int	center[4] = {27, 28, 35, 36};

	for (int i = 0; i < 4; i++)
	{
		int square = center[i];
		int piece = pos->board[square];

		if (piece != NO_PIECE)
			score[COLOR(piece)] += 100;
	}
}

void	king_safety(const struct position *pos, int *score)
{
	int	king_square[2] = {-1, -1};

	for (int square = 0; square < 64; square++)
	{
		int piece = pos->board[square];
		if (piece == PIECE(WHITE, KING))
			king_square[WHITE] = square;
		else if (piece == PIECE(BLACK, KING))
			king_square[BLACK] = square;
	}

	int king_neighbours[8] = {-1, 1, -8, 8, -7, 7, -9, 9};

	for (int side = 0; side <= 1; side++)
	{
		if (king_square[side] == -1)
			continue ;
		for (int i = 0; i < 8; i++)
		{
			int neighbour_square = king_square[side] + king_neighbours[i];
			if (neighbour_square >= 0 && neighbour_square < 64)
			{
				int piece = pos->board[neighbour_square];
				if (piece != NO_PIECE && COLOR(piece) == side)
					score[side] += 50;
				else if (piece != NO_PIECE && COLOR(piece) != side)
					score[side] -= 50;
			}
		}
	}
}

int	is_isolated_pawn(const struct position *pos, int square, int side)
{
	int file = FILE(square);
	int rank = RANK(square);

	if (file > 0)
	{
		int left_pawn = square - 1;
		if ((pos->board[left_pawn] == PIECE(side, PAWN))
			|| (rank < 7 && pos->board[left_pawn + 8] == PIECE(side, PAWN))
			|| (rank > 0 && pos->board[left_pawn - 8] == PIECE(side, PAWN)))
				return (0);
	}
	if (file < 7)
	{
		int right_pawn = square + 1;
		if ((pos->board[right_pawn] == PIECE(side, PAWN))
			|| (rank < 7 && pos->board[right_pawn + 8] == PIECE(side, PAWN))
			|| (rank > 0 && pos->board[right_pawn - 8] == PIECE(side, PAWN)))
				return (0);
	}
	return (1);
}

int	is_doubled_pawn(const struct position *pos, int square, int side)
{
	int	file = FILE(square);
	int	rank = RANK(square);

	if ((rank > 0 && pos->board[square - 8] == PIECE(side, PAWN)) ||
		(rank < 7 && pos->board[square + 8] == PIECE(side, PAWN)))
			return (1);
	return (0);
}

int	is_passed_pawn(const struct position *pos, int square, int side)
{
	int	file = FILE(square);
	int	direction = (side == WHITE) ? -8 : 8;
	int	opponent_pawn = PIECE(1 - side, PAWN);

	for (int i = 1; i <= 7; i++)
	{
		int front_square = square + direction * i;
		if (front_square < 0 || front_square >= 64)
			break ;
		if ((file > 0 && pos->board[front_square - 1] == opponent_pawn)
			|| (pos->board[front_square] == opponent_pawn)
			|| (file < 7 && pos->board[front_square + 1] == opponent_pawn))
				return (0);
	}
	return (1);
}

void	pawn_structure(const struct position *pos, int *score)
{
	for (int square = 0; square < 64; square++)
	{
		int piece = pos->board[square];
		if (TYPE(piece) == PAWN)
		{
			int side = COLOR(piece);
			if (is_isolated_pawn(pos, square, side))
				score[side] -= 100;
			if (is_doubled_pawn(pos, square, side))
				score[side] -= 50;
			if (is_passed_pawn(pos, square, side))
				score[side] += 100;
		}
	}
}

void	blocked_pieces(const struct position *pos, int *score)
{
	for (int square = 0; square < 64; square++)
	{
		int piece = pos->board[square];
		if (piece == NO_PIECE)
			continue;

		int side = COLOR(piece);

		if (TYPE(piece) == PAWN)
		{
			int direction = (side == WHITE) ? 8 : -8;
			int front_square = square + direction;
			if (front_square >= 0 && front_square < 64 && pos->board[front_square] != NO_PIECE)
				score[side] -= 100;
		}
		else if (TYPE(piece) == KNIGHT)
		{
			int knight_moves[8] = {-17, -15, -10, -6, 6, 10, 15, 17};
			int blocked_count = 0;

			for (int i = 0; i < 8; i++)
			{
				int target_square = square + knight_moves[i];
				if (target_square < 0 || target_square >= 64)
					continue;
				if (pos->board[target_square] != NO_PIECE && COLOR(pos->board[target_square]) == side)
					blocked_count++;
			}
			score[side] -= (blocked_count * 100);
		}
		else if (TYPE(piece) == BISHOP || TYPE(piece) == QUEEN)
		{
			int directions[4] = {-9, 9, -7, 7};

			for (int d = 0; d < 4; d++)
			{
				int dir = directions[d];
				int target_square = square + dir;

				while (target_square >= 0 && target_square < 64 &&
						abs((target_square % 8) - (square % 8)) <= 7)
				{
					if (pos->board[target_square] != NO_PIECE)
					{
						if (COLOR(pos->board[target_square]) == side)
							score[side] -= 100;
						break;
					}
					target_square += dir;
				}
			}
		}
		if (TYPE(piece) == ROOK || TYPE(piece) == QUEEN)
		{
			int directions[4] = {-8, 8, -1, 1};

			for (int d = 0; d < 4; d++)
			{
				int dir = directions[d];
				int target_square = square + dir;

				while (target_square >= 0 && target_square < 64 &&
						((dir == -1 || dir == 1) ? (target_square / 8 == square / 8) : 1))
				{
					if (pos->board[target_square] != NO_PIECE)
					{
						if (COLOR(pos->board[target_square]) == side)
							score[side] -= 100;
						break;
					}
					target_square += dir;
				}
			}
		}
	}
}

int	init_pst(int ****table)
{
	int	i;
	int	j;

	int pawntable[2][64] =
	{
	{
		0,    0,    0,    0,    0,    0,    0,    0,
		50,   50,   50,   50,   50,   50,   50,   50,
		10,   10,   20,   30,   30,   20,   10,   10,
		 5,    5,   10,   25,   25,   10,    5,    5,
		 0,    0,    0,   20,   20,    0,    0,    0,
		10,   10,   10,   40,   40,   10,   10,   10,
		 5,    0,    5,    5,    5,    5,    0,    5,
		 0,    0,    0,    0,    0,    0,    0,    0

	},
	{
		0,     0,   0,   0,   0,   0,   0,   0,
		178, 173, 158, 134, 147, 132, 165, 187,
		94,  100,  85,  67,  56,  53,  82,  84,
		32,   24,  13,   5,  -2,   4,  17,  17,
		13,    9,  -3,  -7,  -7,  -8,   3,  -1,
		4,     7,  -6,   1,   0,  -5,  -1,  -8,
		13,    8,   8,  10,  13,   0,   2,  -7,
		0,     0,   0,   0,   0,   0,   0,   0,
	}
	};

	int knighttable[2][64] =
	{
	{
		-167, -89, -34, -49,  61, -97, -15, -107,
		-73,  -41,  72,  36,  23,  62,   7,  -17,
		-47,   60,  37,  65,  84, 129,  73,   44,
		-9,    17,  19,  53,  37,  69,  18,   22,
		-13,    4,  16,  13,  28,  19,  21,   -8,
		-23,   -9,  12,  10,  19,  17,  25,  -16,
		-29,  -53, -12,  -3,  -1,  18, -14,  -19,
		-105, -21, -58, -33, -17, -28, -19,  -23,
	},
	{
		-58, -38, -13, -28, -31, -27, -63, -99,
		-25,  -8, -25,  -2,  -9, -25, -24, -52,
		-24, -20,  10,   9,  -1,  -9, -19, -41,
		-17,   3,  22,  22,  22,  11,   8, -18,
		-18,  -6,  16,  25,  16,  17,   4, -18,
		-23,  -3,  -1,  15,  10,  -3, -20, -22,
		-42, -20, -10,  -5,  -2, -20, -23, -44,
		-29, -51, -23, -15, -22, -18, -50, -64,
	}
	};

	int bishoptable[2][64] =
	{
	{
		-29,   4, -82, -37, -25, -42,   7,  -8,
		-26,  16, -18, -13,  30,  59,  18, -47,
		-16,  37,  43,  40,  35,  50,  37,  -2,
		-4,    5,  19,  50,  37,  37,   7,  -2,
		-6,   13,  13,  26,  34,  12,  10,   4,
		0,    15,  15,  15,  14,  27,  18,  10,
		4,    15,  16,   0,   7,  21,  33,   1,
		-33,  -3, -14, -21, -13, -12, -39, -21,
	},
	{
		-14, -21, -11,  -8, -7,  -9, -17, -24,
		-8,   -4,   7, -12, -3, -13,  -4, -14,
		2,    -8,   0,  -1, -2,   6,   0,   4,
		-3,    9,  12,   9, 14,  10,   3,   2,
		-6,    3,  13,  19,  7,  10,  -3,  -9,
		-12,  -3,   8,  10, 13,   3,  -7, -15,
		-14, -18,  -7,  -1,  4,  -9, -15, -27,
		-23,  -9, -23,  -5, -9, -16,  -5, -17,
	}
	};

	int rooktable[2][64] =
	{
	{
		32,   42,  32,  51, 63,  9,  31,  43,
		27,   32,  58,  62, 80, 67,  26,  44,
		-5,   19,  26,  36, 17, 45,  61,  16,
		-24, -11,   7,  26, 24, 35,  -8, -20,
		-36, -26, -12,  -1,  9, -7,   6, -23,
		-45, -25, -16, -17,  3,  0,  -5, -33,
		-44, -16, -20,  -9, -1, 11,  -6, -71,
		-19, -13,   1,  17, 16,  7, -37, -26,
	},
	{
		13, 10, 18, 15, 12,  12,   8,   5,
		11, 13, 13, 11, -3,   3,   8,   3,
		7,  7,  7,  5,  4,  -3,  -5,  -3,
		4,  3, 13,  1,  2,   1,  -1,   2,
		3,  5,  8,  4, -5,  -6,  -8, -11,
		-4,  0, -5, -1, -7, -12,  -8, -16,
		-6, -6,  0,  2, -9,  -9, -11,  -3,
		-9,  2,  3, -1, -5, -13,   4, -20,
	}
	};

	int queentable[2][64] =
	{
	{
	  -28,   0,  29,  12,  59,  44,  43,  45,
	  -24, -39,  -5,   1, -16,  57,  28,  54,
	  -13, -17,   7,   8,  29,  56,  47,  57,
	  -27, -27, -16, -16,  -1,  17,  -2,   1,
	   -9, -26,  -9, -10,  -2,  -4,   3,  -3,
	  -14,   2, -11,  -2,  -5,   2,  14,   5,
	  -35,  -8,  11,   2,   8,  15,  -3,   1,
	   -1, -18,  -9,  10, -15, -25, -31, -50,
	},
	{
	   -9,  22,  22,  27,  27,  19,  10,  20,
	  -17,  20,  32,  41,  58,  25,  30,   0,
	  -20,   6,   9,  49,  47,  35,  19,   9,
		3,  22,  24,  45,  57,  40,  57,  36,
	  -18,  28,  19,  47,  31,  34,  39,  23,
	  -16, -27,  15,   6,   9,  17,  10,   5,
	  -22, -23, -30, -16, -16, -23, -36, -32,
	  -33, -28, -22, -43,  -5, -32, -20, -41,
	}
	};

	int kingtable[2][64] =
	{
	{
	  -65,  23,  16, -15, -56, -34,   2,  13,
	   29,  -1, -20,  -7,  -8,  -4, -38, -29,
	   -9,  24,   2, -16, -20,   6,  22, -22,
	  -17, -20, -12, -27, -30, -25, -14, -36,
	  -49,  -1, -27, -39, -46, -44, -33, -51,
	  -14, -14, -22, -46, -44, -30, -15, -27,
		1,   7,  -8, -64, -43, -16,   9,   8,
	  -15,  36,  12, -54,   8, -28,  24,  14,
	},
	{
	  -74, -35, -18, -18, -11,  15,   4, -17,
	  -12,  17,  14,  17,  17,  38,  23,  11,
	   10,  17,  23,  15,  20,  45,  44,  13,
	   -8,  22,  24,  27,  26,  33,  26,   3,
	  -18,  -4,  21,  24,  27,  23,   9, -11,
	  -19,  -3,  11,  21,  23,  16,   7,  -9,
	  -27, -11,   4,  13,  14,   4,  -5, -17,
	  -53, -34, -21, -11, -28, -14, -24, -43
	}
	};

	*table = malloc(sizeof(int **) * 6);

	for (i = 0; i < 6; i++)
	{
		(*table)[i] = malloc(sizeof(int *) * 2);
		for (j = 0; j < 2; j++)
			(*table)[i][j] = malloc(sizeof(int) * 64);
	}

	for (i = 0; i < 6; i++)
		for (j = 0; j < 2; j++)
			if (!(*table)[i][j])
				return (free_this_monster(table), -1);

	for (j = 0; j < 2; j++)
	{
		for (i = 0; i < 64; i++)
		{
			(*table)[PAWN][j][i] = pawntable[j][i];
			(*table)[KNIGHT][j][i] = knighttable[j][i];
			(*table)[BISHOP][j][i] = bishoptable[j][i];
			(*table)[ROOK][j][i] = rooktable[j][i];
			(*table)[QUEEN][j][i] = queentable[j][i];
			(*table)[KING][j][i] = kingtable[j][i];
		}
	}
	return (0);
}

void	free_this_monster(int ****table)
{
	int	i;
	int	j;

	if (table == NULL || *table == NULL)
		return ;
	for (i = 0; i < 6; i++)
	{
		if ((*table)[i] == NULL)
			continue ;
		for (j = 0; j < 2; j++)
			free((*table)[i][j]);
		free((*table)[i]);
	}
	free(*table);
	*table = NULL;
}

int	get_game_stage(const int *board)
{
	int	i;
	int	count;

	count = 0;
	for (i = 0; i < 64; i++)
	{
		if (board[i] != NO_PIECE)
			count++;
	}
	if (count <= 8)
		return (1);
	return (0);
}
